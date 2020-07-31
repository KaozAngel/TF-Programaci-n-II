#ifndef _GLOBAL_DATA_H_
#define _GLOBAL_DATA_H_


#include <sstream>
#include<vector>
#include<string>
#include<iostream>

#include <msclr\marshal_cppstd.h>

#define TOTAL_CARDS 14
#define NUMBER_CARDS 10

#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 200

#define OPONENTE_WIDTH 50
#define OPONENTE_HEIGHT 100

#define CARD_SPACING_X 40
#define CARD_SPACING_X_OP 20
#define CARD_SPACING_Y 20

#define NUM_CARTA_DECK 7

#define NUM_IDS 112

using namespace std;
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

enum Carta_Efecto {Roba2,Cambio,Salta,Comodin,Roba4,Efecto_Error};

enum Card_Color {Red=0,Blue=1,Yellow=2,Green=3,Black=4};

enum Fase_Juego { Enter_to_Start,Primer_Menu, Escoger_Primero, Juego, Repartir_Cartas};

static class GlobalData {

	
public:
	static vector<pair<int, int>>& PosIniJugadores()
	{ 
		static vector<pair<int, int>>posIniJugadores; 
		return posIniJugadores; 
	}
	
	
	static void setPosIniJugadores(Graphics^g) 
	{
		GlobalData::PosIniJugadores() = vector<pair<int, int>>(5);
		for (int i = 0; i < 5; i++) 
		{
			switch (i)
			{
			case 0:
				GlobalData::PosIniJugadores()[i].first = ((g->VisibleClipBounds.Width / 2) - (NUM_CARTA_DECK / 2)*CARD_SPACING_X);
				GlobalData::PosIniJugadores()[i].second = (g->VisibleClipBounds.Height) - PLAYER_HEIGHT;
				break;
			case 1:
				GlobalData::PosIniJugadores()[i].first = (g->VisibleClipBounds.Width) - OPONENTE_WIDTH;
				GlobalData::PosIniJugadores()[i].second = (g->VisibleClipBounds.Height) - (NUM_CARTA_DECK*CARD_SPACING_Y) - OPONENTE_HEIGHT;
				break;					   
			case 2:						   
				GlobalData::PosIniJugadores()[i].first = (g->VisibleClipBounds.Width) - (NUM_CARTA_DECK*CARD_SPACING_X_OP) - OPONENTE_WIDTH;
				GlobalData::PosIniJugadores()[i].second = 0;
				break;					   
			case 3:						   
				GlobalData::PosIniJugadores()[i].first = 0;
				GlobalData::PosIniJugadores()[i].second = 0;
				break;					   
			case 4:						   
				GlobalData::PosIniJugadores()[i].first = 0;
				GlobalData::PosIniJugadores()[i].second = (g->VisibleClipBounds.Height) - (NUM_CARTA_DECK*CARD_SPACING_Y) - OPONENTE_HEIGHT;
				break;					   
			default:					   
				GlobalData::PosIniJugadores()[i].first = 0;
				GlobalData::PosIniJugadores()[i].second = 0;
				break;
			}
		}
		
	}

	//Retorna el nombre de la carta
	static string NameFrom(int id) {
		int mid = id % 14;
		string aux="";
		string val = to_string(mid);
		if(mid<NUMBER_CARDS){
			aux = "Numero ";
			return aux + val;
		}
		else
		{
			switch (mid)
			{
			case 10:
				aux = "Roba Dos";
				break;
			case 11:
				aux = "Revertir Orden";
				break;
			case 12:
				aux = "Salta el Turno";
				break;
			case 13:
				if(id>=NUM_IDS/2)
					aux = "Cambio de Color";
				else
					aux = "Roba Cuatro";
				break;
			default:
				aux = "No existe esa carta";
				break;
			}
			return aux;
		}
		
	}
	//Retorna el efecto de una carta en base a su id
	static Carta_Efecto EffectFrom(int id)
	{
		int mid = id % 14;
		Carta_Efecto aux;
		switch (mid)
		{
		case 10:
			aux = Roba2;
			break;
		case 11:
			aux = Cambio;
			break;
		case 12:
			aux = Salta;
			break;
		case 13:
			if (id >= NUM_IDS / 2)
				aux = Comodin;
			else
				aux = Roba4;
			break;
		default:
			aux = Efecto_Error;
			break;
		}
		return aux;
	}

	static vector<int>SortInts(vector<int>vec) 
	{
		for (int i = 0; i < vec.size()-1; i++) 
		{
			for (int j = 0; j < vec.size(); j++) 
			{
				if (vec[i] > vec[i + 1]) 
				{
					int aux = vec[i];
					vec[i] = vec[i + 1];
					vec[i + 1] = aux;
				}
			}
		}
	}
	
};

#endif // !_GLOBAL_DATA_H_

