#include "Card.h"


Carta::Carta(int id, int px, int py, int width, int height) {
	this->id = id;
	this->fileName = "./img/UNO_deck.png";
	this->px = px;
	this->py = py;
	this->reversed = false;
	this->width = width;
	this->height = height;
}
Carta::Carta(int id, Card_Color color, int px, int py, bool reversed, int width, int height) {
	this->id = id;
	this->color = color;
	this->px = px;
	this->py = py;
	this->reversed = reversed;
	this->width = width;
	this->height = height;
	this->name = GlobalData::NameFrom(id);
	if (this->reversed)
	{
		this->fileName = "./img/UNO_Back.png";
	}
	else
	{
		this->fileName = "./img/UNO_deck.png";
	}


}
Carta::~Carta() {}


int Carta::getId() { return id; }
int Carta::getPx() { return px; }
int Carta::getPy() { return py; }
bool Carta::getReversed() { return reversed; }
Card_Color Carta::getColor() { return color; }
string Carta::getName() { return name; }
string Carta::getFileName() { return fileName; }

void Carta::setPx(int px) { this->px = px; }
void Carta::setPy(int py) { this->py = py; }
void Carta::setReversed(bool reversed)
{
	this->reversed = reversed;
	if (this->reversed)
	{
		this->fileName = "./img/UNO_Back.png";
	}
	else
	{
		this->fileName = "./img/UNO_deck.png";
	}
}
void Carta::setColor(Card_Color color) { this->color = color; }
void Carta::setName(string name) { this->name = name; }
void Carta::setFileName(string fileName) { this->fileName = fileName; }

void Carta::DibujarCarta(Graphics^g) {
	Bitmap^ bmp = gcnew Bitmap(gcnew String(fileName.c_str()));
	if (this->reversed)
	{
		g->DrawImage(bmp, px, py, width, height);
	}
	else
	{
		float w = (bmp->Width / 14);
		float h = (bmp->Height / 8);
		int indx = id % 14;
		int indy = id / 14;
		Drawing::Rectangle r_origen(w*indx, h*indy, w, h);
		Drawing::Rectangle r_destino(px, py, width, height);
		g->DrawImage(bmp, r_destino, r_origen, GraphicsUnit::Pixel);
	}

	delete bmp;
}
void Carta::MoverCarta() {}
