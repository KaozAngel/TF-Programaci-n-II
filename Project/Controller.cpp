#include"Controller.h"




Controlador::Controlador(Graphics^g)
{
	
	GlobalData::setPosIniJugadores(g);
	selectInd = 0;
	fase = Enter_to_Start;
	tablero->StartCartasLibres();
	numJugadores = 2;
	tablero = new Tablero(g,numJugadores);
	
}
Controlador::Controlador(int numJugadores, Graphics^g)
{
	GlobalData::setPosIniJugadores(g);
	selectInd = 0;
	fase = Enter_to_Start;
	this->numJugadores = numJugadores;
	tablero = new Tablero(g, numJugadores);
	tablero->StartCartasLibres();
	
}
Controlador::~Controlador() {}

int Controlador::getNumJugadores() { return tablero->getNumJugadores(); }
void Controlador::setNumJugadores(int numJugadores) { tablero->setNumJugadores(numJugadores); }

Tablero* Controlador::getTablero() { return tablero; }


void Controlador::ResetGame()
{
	tablero->ResetCartasLibres();
	tablero->ResetDecks();
}


void Controlador::EnterToStart(Graphics^g)
{
	int x = g->VisibleClipBounds.Width / 2;
	int y = g->VisibleClipBounds.Height / 2;
	StringFormat ^f = gcnew StringFormat();
	f->Alignment = StringAlignment::Center;
	Font ^font = gcnew Font("Comic Sans", 20, FontStyle::Bold);
	g->DrawString("PRESIONA ENTER PARA EMPEZAR", font, Brushes::Black, x, y, f);
}
void Controlador::PrimerMenu(Graphics^g)
{
	int nJugadores = tablero->getNumJugadores();
	if (nJugadores > 5)
	{
		nJugadores = 2;
	}
	if (nJugadores < 2)
	{
		nJugadores = 5;
	}
	vector<string>menu = { "INICIAR JUEGO","NUMERO DE JUGADORES",to_string(nJugadores),"NOMBRE DE JUGADORES","SALIR" };
	int x = g->VisibleClipBounds.Width / 2;
	int y = (g->VisibleClipBounds.Height / 2) - ((menu.size() / 2) * 100);
	StringFormat ^f = gcnew StringFormat();
	f->Alignment = StringAlignment::Center;
	Font ^font = gcnew Font("Comic Sans", 15, FontStyle::Bold);

	for (int i = 0; i < menu.size(); i++)
	{
		g->DrawString(gcnew String(menu[i].c_str()), font, Brushes::Black, x, (y + (80 * i)), f);
	}
	if (selectInd < 0) { selectInd = menu.size() - 1; }
	if (selectInd > menu.size() - 1) { selectInd = 0; }
	DibujarSelector(g, x - 150, y + 10 + (80 * selectInd), 300);
}
void Controlador::DibujarSelector(Graphics^g, int x, int y, int width)
{
	cli::array<Point>^ triangle_left = { Point(x,y), Point(x - 40,y + 15), Point(x - 40,y - 15) };
	cli::array<Point>^ triangle_right = { Point(x + width,y), Point(x + width + 40,y + 15), Point(x + width + 40,y - 15) };
	g->FillPolygon(Brushes::Black, triangle_left);
	g->FillPolygon(Brushes::Black, triangle_right);
}
void Controlador::DibujarPantalla(Graphics^g)
{
	switch (fase)
	{
	case Enter_to_Start:
		EnterToStart(g);
		break;
	case Primer_Menu:
		PrimerMenu(g);
		break;
	case Escoger_Primero:
		tablero->DibujarSorteo(g);
		break;
	case Juego:
		tablero->DibujarRepartir(g);
		break;
	case Repartir_Cartas:
		break;
	default:
		break;
	}
}
int Controlador::MenuOptions()
{
	switch (selectInd)
	{
	case 0:
		fase = Escoger_Primero;
		tablero->EscogerPrimero();
		break;
	case 3:
		return 2;
		break;
	case 4:
		fase = Enter_to_Start;
		break;
	default:
		break;
	}
	return 1;
}
int Controlador::ProcesarTecla(int key)
{
	switch (fase)
	{
	case Enter_to_Start:
		if (key == int(Keys::Enter))
		{
			fase = Primer_Menu;
		}
		else if (key == int(Keys::Escape))
		{
			return 0;
		}
		break;
	case Primer_Menu:
		if (key == int(Keys::Escape))
		{
			fase = Enter_to_Start;
		}
		switch (key)
		{
		case int(Keys::Up) :
			selectInd--;
			if (selectInd == 2)selectInd--;
			break;
		case int(Keys::Down) :
			selectInd++;
			if (selectInd == 2)selectInd++;
			break;
		case int(Keys::Left) :
			if (selectInd == 1)
			{
				tablero->setNumJugadores(tablero->getNumJugadores() - 1);
			}
							 break;
		case int(Keys::Right) :
			if (selectInd == 1)
			{
				tablero->setNumJugadores(tablero->getNumJugadores() + 1);
			}
							  break;
		case int(Keys::Enter) :
			return MenuOptions();
			break;
		default:

			break;
		}
		break;
	case Escoger_Primero:
		tablero->KeyPress(key, fase);
		break;
	case Juego:
		tablero->KeyPress(key, fase);
		break;
	default:
		break;
	}

	return 1;
}