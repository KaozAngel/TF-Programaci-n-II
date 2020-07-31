#ifndef _NUMBER_CARD_H_
#define _NUMBER_CARD_H_

#include "Card.h"

class CartaNumero :public Carta{
private:
	int number;
public:
	CartaNumero(int, int, int, int, int);
	CartaNumero(int, Card_Color, int, int, bool, int, int);
	~CartaNumero();

	int getNumber();
	void setNumber(int number);

};

#endif // !_NUMBER_CARD_H_

