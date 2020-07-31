#include"Board.h"

Tablero::Tablero(Graphics^g,int numJugadores) 
{
	this->screenWidth = g->VisibleClipBounds.Width;
	this->screenHeight = g->VisibleClipBounds.Height;
	this->numJugadores = numJugadores;
	this->deckEscoger = new Deck();
	this->deckMesa = new Deck();
	for (int i = 0; i < numJugadores; i++)
	{
		vecJugadores.push_back(new Jugador(i));
	}
}
Tablero::~Tablero() {}


int Tablero::getNumJugadores() { return numJugadores; }
void Tablero::setNumJugadores(int numJugadores) { this->numJugadores = numJugadores; }
Deck* Tablero::getDeckEscoger() { return deckEscoger; }
Deck* Tablero::getDeckMesa() { return deckMesa; }
vector<int> Tablero::getCartasLibres() { return cartasLibres; }
vector<Jugador*> Tablero::getJugadores() { return vecJugadores; }

void Tablero::setVecJugadores(vector<Jugador*>vecJugadores) { this->vecJugadores = vecJugadores; }

void Tablero::setNames(cli::array<String^>^names) 
{
	msclr::interop::marshal_context context;
	for (int i = 0; i < numJugadores; i++)
	{
		string nombre = context.marshal_as<std::string>(names[i]);
		vecJugadores[i]->setNombre(nombre);
	}
}

void Tablero::StartCartasLibres() 
{
	for (int i = 0; i < NUM_IDS; i++)
	{
		cartasLibres.push_back(1);
	}
}

void Tablero::StartJugadores() 
{
	
	vecJugadores.clear();
	for (int i = 0; i < numJugadores; i++) 
	{
		vecJugadores.push_back(new Jugador(i));
	}

}

void Tablero::ResetCartasLibres() 
{
	cartasLibres.clear();
	StartCartasLibres();
}

void Tablero::EscogerPrimero() 
{
	vector<int>ids = vectorSorteo();
	deckEscoger->ResetDeck();
	for (int i = 0; i < numJugadores; i++)
	{
		deckEscoger->AddCarta(new CartaNumero(
			ids[i],
			((screenWidth / 2) - ((numJugadores / 2)*PLAYER_WIDTH)) + ((PLAYER_WIDTH+40)*i),
			((screenHeight / 2) - (PLAYER_HEIGHT / 2)),
			PLAYER_WIDTH,
			PLAYER_HEIGHT
		));
	}
	ordenarJugadores();	
}

void Tablero::DibujarSorteo(Graphics^g) 
{
	for (int i = 0; i<numJugadores; i++)
	{
		deckEscoger->getPos(i)->DibujarCarta(g);

		g->DrawString(gcnew String(
			vecJugadores[i]->getNombre().c_str()),
			SystemFonts::DefaultFont,
			Brushes::Black,
			deckEscoger->getDeck()[i]->getPx(),
			deckEscoger->getDeck()[i]->getPy() + PLAYER_HEIGHT + 10
		);
		if (vecJugadores[i]->getNumeroOrden()==numJugadores-1) 
		{
			g->DrawRectangle(
				gcnew Pen(Brushes::Black, 5),
				deckEscoger->getPos(i)->getPx()-5,
				deckEscoger->getPos(i)->getPy()-5,
				PLAYER_WIDTH+10,
				PLAYER_HEIGHT+40
			);
		}
	}
}

vector<int> Tablero::vectorSorteo() 
{
	Random r;
	vector<int> ids;
	bool pass = true;
	for (int i = 0; i < numJugadores; i++)
	{
		pass = true;
		int id = r.Next(0, 112);
		if (id % 14 > 9)
		{
			i--;
			continue;
		}
		for (int j = 0; j < ids.size(); j++) 
		{
			if (id%14 == ids[j]%14) 
			{
				i--;
				pass = false;
				break;
				
			}
		}
		if(pass)
			ids.push_back(id);
	}
	return ids;
}

void Tablero::Repartir() {
	Random r;
	vector<vector<int>>vecJugId = vector<vector<int>>(numJugadores);
	for (int i = 0; i < NUM_CARTA_DECK; i++)
	{
		for (int j = 0; j < numJugadores; j++)
		{
			int id = r.Next(0, 112);
			if (cartasLibres[id])
			{
				cartasLibres[id] = 0;
				vecJugId[j].push_back(id);
			}
			else
			{
				j--;
			}
		}
	}
	for (int i = 0; i < numJugadores; i++)
	{
		vecJugadores[i]->Repartir(vecJugId[i]);
	}
}

void Tablero::DibujarRepartir(Graphics^g) 
{
	DibujarJugadores(g);
}

void Tablero::ordenarJugadores() 
{
	int max= ((CartaNumero*)(deckEscoger->getPos(0)))->getNumber();
	int indice = 0;
	vecJugadores[0]->setNumeroOrden(numJugadores - 1);

	for (int i = 0; i < numJugadores; i++) 
	{
		int n1 = ((CartaNumero*)(deckEscoger->getPos(i)))->getNumber();
		if (n1 > max)
		{
			max = n1;
			vecJugadores[i]->setNumeroOrden(numJugadores-1);
			indice = i;
		}
	}
	int cont = 0;
	for (int i = indice + 1; i < numJugadores; i++) 
	{
		vecJugadores[i]->setNumeroOrden(cont);
		cont++;
	}
	for (int i = 0; i < indice; i++)
	{
		vecJugadores[i]->setNumeroOrden(cont);
		cont++;
	}
}

void Tablero::KeyPress(int key,Fase_Juego &fase) 
{
	if (fase == Escoger_Primero) 
	{
		switch (KeysEscoger(key)) 
		{
		case 0:fase = Primer_Menu; break;
		case 1:fase = Juego; break;
		case -1:EscogerPrimero(); break;
		default:break;
		}
	}
	else if(fase == Juego)
	{
		switch (KeysJuego(key))
		{
		case 0: 
			fase = Primer_Menu;
			ResetCartasLibres();
			ResetDecks();
			break;
		case 1:
			ResetCartasLibres();
			ResetDecks();
			Repartir();
			break;
		default:break;
		}
	}
}

int Tablero::KeysJuego(int key) 
{
	if (key == int(Keys::Enter))
	{
		return 1;
	}
	if (key == int(Keys::Escape))return 0;
}

int Tablero::KeysEscoger(int key)
{
	if (key == int(Keys::Enter)) 
	{
		Repartir();
		return 1;
	}
	if (key == int(Keys::A)) { return -1; }
	if (key == int(Keys::Escape))return 0;
	return 2;
}

void Tablero::DibujarJugadores(Graphics^g) 
{
	for (int i = 0; i < numJugadores; i++)
	{
		vecJugadores[i]->DibujarDeck(g);
		vecJugadores[i]->DibujarNombre(g);
	}
}

void Tablero::ResetDecks() 
{
	for (int i = 0; i < vecJugadores.size(); i++) 
	{
		vecJugadores[i]->ResetDeck();
	}
}