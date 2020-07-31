#include"NumberCard.h"

CartaNumero::CartaNumero(int id,int px,int py,int width,int height):Carta(id,px,py,width,height)
{
	this->number = id % 14;
}
CartaNumero::CartaNumero(int id, Card_Color color, int px, int py, bool reversed,int width,int height) :
	Carta(id, color, px, py, reversed, width, height)
{
	this->number = id % 14;
}
CartaNumero::~CartaNumero() {}

int CartaNumero::getNumber() { return number; }
void CartaNumero::setNumber(int number) { this->number = number; }