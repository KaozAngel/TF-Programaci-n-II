#pragma once

#include"GlobalData.h"
#include"NumberCard.h"
#include"EffectCard.h"

class Deck {
private:
	vector<Carta*> vectorCartas;
public:
	
	Deck();
	
	~Deck();

	//Añade carta al deck
	void AddCarta(Carta *c);

	//Dibuja el Deck en el form 
	void DibujarDeck(Graphics^g);

	//Saca la carta seleccionada
	Carta* SacarCarta(Carta *c);

	int deckSize();
	
	vector<Carta*>getDeck();

	Carta* findBy(int id);

	Carta* getPos(int i);

	void setPos(int pos, Carta*c);

	void ResetDeck();
};
