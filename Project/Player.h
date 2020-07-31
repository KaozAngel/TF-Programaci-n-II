#pragma once
#include"GlobalData.h"
#include"Deck.h"

class Jugador {
private:
	int puntos;
	int numeroOrden;
	bool perdio;
	Deck*deckCartas;
	int posX;
	int posY;
	string nombre;
public:
	Jugador(int numeroOrden);

	~Jugador();

	int getNumeroOrden();
	int getPuntos();
	bool getPerdio();
	Deck* getDeckCartas();
	string getNombre();

	void setNumeroOrden(int numerOrden);
	void setPuntos(int puntos);
	void setPerdio(bool perdio);
	void setDeckCartas(Deck*deck);
	void setNombre(string nombre);

	void DibujarDeck(Graphics^g);

	void JugarCarta(Carta*c);

	void CogerCartas(vector<int> vecIds);

	void Repartir(vector<int> vecIds);

	void ResetDeck();

	void PosInicial();

	void DibujarNombre(Graphics^g);

	pair<int, int>PosicionNombres();
};
