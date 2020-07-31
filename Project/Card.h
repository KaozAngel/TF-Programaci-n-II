#pragma once
#ifndef _CARD_H_
#define _CARD_H_

#include"GlobalData.h"


class Carta {
protected:
	int id;
	int px, py;
	int width, height;
	int value;
	string name;
	Card_Color color;
	string fileName;
	bool reversed;
public:
	Carta(int id,int px, int py, int width, int height);
	Carta(int id,Card_Color color,int px, int py,bool reversed,int width,int height);
	~Carta();

	//--------------------------------

	//Getters y setters

	int getId();
	int getPx();
	int getPy();
	bool getReversed();
	Card_Color getColor();
	string getName();
	string getFileName();

	void setPx(int px);
	void setPy(int py);
	void setReversed(bool reversed);
	void setColor(Card_Color color);
	void setName(string name);
	void setFileName(string fileName);
	//---------------------------------

	void DibujarCarta(Graphics^g);
	void MoverCarta();
};

#endif // !_CARD_H_

