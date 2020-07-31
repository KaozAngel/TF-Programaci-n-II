#include"EffectCard.h"

CartaEfecto::CartaEfecto(int id, int px, int py, int width, int height) :Carta(id, px, py, width, height)
{
	this->efecto = GlobalData::EffectFrom(id);
}
CartaEfecto::CartaEfecto(int id, Card_Color color, int px, int py, bool reversed, int width, int height) :
	Carta(id, color, px, py, reversed, width, height)
{
	this->efecto = GlobalData::EffectFrom(id);
}
CartaEfecto::~CartaEfecto() {}

Carta_Efecto CartaEfecto::getEfecto() { return efecto; }
void CartaEfecto::setEfecto(Carta_Efecto efecto) { this->efecto = efecto; }