#include"Deck.h"

Deck::Deck() {}
Deck::~Deck() {}

vector<Carta*>Deck::getDeck() { return vectorCartas; }

void Deck::AddCarta(Carta *c)
{
	vectorCartas.push_back(c);
}

void Deck::DibujarDeck(Graphics^g)
{
	for (int i = 0; i < vectorCartas.size(); i++)
	{
		vectorCartas[i]->DibujarCarta(g);
	}
}

int Deck::deckSize() {
	return vectorCartas.size();
}

Carta* Deck::findBy(int id) 
{
	for (int i = 0; i < vectorCartas.size(); i++) 
	{
		if (vectorCartas[i]->getId() == id) 
		{
			return vectorCartas[i];
		}
	}
	return nullptr;
}

Carta* Deck::getPos(int i) 
{
	return vectorCartas[i];
}

void Deck::setPos(int pos, Carta*c) 
{
	vectorCartas[pos] = c;
}

void Deck::ResetDeck() 
{
	vectorCartas.clear();
}