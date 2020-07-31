#ifndef _CARTA_EFECTO_H_
#define _CARTA_EFECTO_H_

#include"Card.h"

class CartaEfecto :public Carta{
private:
	Carta_Efecto efecto;
public:
	CartaEfecto(int,int,int,int,int);
	CartaEfecto(int, Card_Color, int, int, bool,int,int);
	~CartaEfecto();

	Carta_Efecto getEfecto();
	void setEfecto(Carta_Efecto efecto);
};

#endif // !_CARTA_EFECTO_H_

