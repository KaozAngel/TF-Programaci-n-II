#pragma once

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_



#include"Board.h"

class Controlador {
private:
	Fase_Juego fase;
	int turno;
	int numJugadores;
	Tablero* tablero;
	int selectInd;

public:
	Controlador(Graphics^g);
	Controlador(int numJugadores,Graphics^g);
	~Controlador();

	int getNumJugadores();
	void setNumJugadores(int numJugadores);

	Tablero* getTablero();

	void ResetGame();
	
	void EnterToStart(Graphics^g);

	void PrimerMenu(Graphics^g);

	int ProcesarTecla(int key);

	void DibujarPantalla(Graphics^g);

	void DibujarSelector(Graphics^g,int x, int y,int width);

	int MenuOptions();
};

#endif // !_CONTROLLER_H_