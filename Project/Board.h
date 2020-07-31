#pragma once
#include"GlobalData.h"
#include"Player.h"

class Tablero 
{
private:
	int numJugadores;
	int turno;

	int screenWidth;
	int screenHeight;
	Deck* deckEscoger;
	Deck* deckMesa;
	vector<int> cartasLibres;
	vector<Jugador*>vecJugadores;
public:
	Tablero(Graphics^g,int numJugadores);
	~Tablero();

	int getNumJugadores();
	void setNumJugadores(int numJugadores);
	Deck* getDeckEscoger();
	Deck* getDeckMesa();
	vector<int> getCartasLibres();
	vector<Jugador*> getJugadores();

	void setNames(cli::array<String^>^names);

	void setVecJugadores(vector<Jugador*>vecJugadores);

	void StartJugadores();

	void StartCartasLibres();

	void ResetCartasLibres();

	void EscogerPrimero();

	void DibujarSorteo(Graphics^g);

	vector<int> vectorSorteo();

	void Repartir();

	void DibujarRepartir(Graphics^g);

	void ordenarJugadores();

	void KeyPress(int key,Fase_Juego &fase);

	int KeysJuego(int key);

	int KeysEscoger(int key);

	void DibujarJugadores(Graphics^g);

	void ResetDecks();
};