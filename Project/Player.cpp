#include "Player.h"


Jugador::Jugador(int numeroOrden)
{
	this->numeroOrden = numeroOrden;
	this->deckCartas = new Deck();
	this->puntos = 0;
	this->PosInicial();
	this->nombre = "Jugador" + to_string(numeroOrden + 1);
}
Jugador::~Jugador() {}


int Jugador::getNumeroOrden() { return numeroOrden; }
int Jugador::getPuntos() { return puntos; }
bool Jugador::getPerdio() { return perdio; }
Deck* Jugador::getDeckCartas() { return deckCartas; }
string Jugador::getNombre() { return nombre; }

void Jugador::setNumeroOrden(int numerOrden) { 
	this->numeroOrden = numerOrden;
	this->PosInicial();
}
void Jugador::setPuntos(int puntos) { this->puntos = puntos; }
void Jugador::setPerdio(bool perdio) { this->perdio = perdio; }
void Jugador::setDeckCartas(Deck*deck) { this->deckCartas = deck; }
void Jugador::setNombre(string nombre) { this->nombre = nombre; }

void Jugador::Repartir(vector<int> ids) {
	for (int i = 0; i < ids.size(); i++)
	{
		if (ids[i] % 14 < 10) 
		{
			deckCartas->AddCarta(new CartaNumero(
				ids[i],
				Card_Color(ids[i] % 4),
				posX + ((numeroOrden == 0 ? CARD_SPACING_X : CARD_SPACING_X_OP) * i)*(numeroOrden != 1 && numeroOrden != 4),
				posY + (CARD_SPACING_Y * i)*(numeroOrden == 1 || numeroOrden == 4),
				false,//numeroOrden!=0,
				numeroOrden != 0 ? OPONENTE_WIDTH : PLAYER_WIDTH,
				numeroOrden != 0 ? OPONENTE_HEIGHT : PLAYER_HEIGHT
			));
		}
		else 
		{
			deckCartas->AddCarta(new CartaEfecto(
				ids[i],
				Card_Color(ids[i] % 4),
				posX + ((numeroOrden == 0 ? CARD_SPACING_X : CARD_SPACING_X_OP) * i)*(numeroOrden != 1 && numeroOrden != 4),
				posY + (CARD_SPACING_Y * i)*(numeroOrden == 1 || numeroOrden == 4),
				false,//numeroOrden!=0,
				numeroOrden != 0 ? OPONENTE_WIDTH : PLAYER_WIDTH,
				numeroOrden != 0 ? OPONENTE_HEIGHT : PLAYER_HEIGHT
			));
		}
		
	}
}

void Jugador::DibujarDeck(Graphics^g)
{
	deckCartas->DibujarDeck(g);
}

void Jugador::ResetDeck()
{
	deckCartas->ResetDeck();
}

void Jugador::PosInicial()
{
	posX = GlobalData::PosIniJugadores()[numeroOrden].first;
	posY = GlobalData::PosIniJugadores()[numeroOrden].second;
}
void Jugador::DibujarNombre(Graphics^g) 
{
	StringFormat^f = gcnew StringFormat();
	f->Alignment = StringAlignment::Center;
	pair<int, int>posN = PosicionNombres();
	g->DrawString(
		gcnew String(this->nombre.c_str()),
		SystemFonts::DefaultFont,
		Brushes::Black,
		posN.first,
		posN.second,
		f
	);

	delete f;
}

pair<int, int>Jugador::PosicionNombres() 
{
	pair<int, int>pos;
	switch (numeroOrden)
	{
	case 0:
		pos.first = posX + ((deckCartas->deckSize()/2)*CARD_SPACING_X); 
		pos.second = posY - 15;
		break;
	case 1: 
		pos.first = posX - nombre.length()*5;
		pos.second = posY + (deckCartas->deckSize()/2)*CARD_SPACING_Y;
		break;
	case 2: 
		pos.first = posX + ((deckCartas->deckSize() / 2)*CARD_SPACING_X_OP);
		pos.second = posY + OPONENTE_HEIGHT + 5;
		break;
	case 3: 
		pos.first = posX + ((deckCartas->deckSize() / 2)*CARD_SPACING_X_OP);
		pos.second = posY + OPONENTE_HEIGHT + 5;
		break;
	case 4: 
		pos.first = posX + OPONENTE_WIDTH + nombre.length() * 5;
		pos.second = posY + (deckCartas->deckSize() / 2)*CARD_SPACING_Y;
		break;
	default:
		pos.first = 0;
		pos.second = 0;
		break;
	}
	return pos;
}