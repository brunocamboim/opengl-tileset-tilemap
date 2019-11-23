#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include "TileSet.h"

class Personagem
{
public:
	Personagem() {}
	~Personagem() {}

	int anterior;
	int movimento;
	float rowActual;
	float colActual;
	float offsetx;
	float offsety;
	TileSet tileSet;
	enum Directions {
		null = -1,
		NORTHEAST = 0,
		EAST = 1,
		SOUTHEAST = 2,
		SOUTH = 3,
		SOUTHWEST = 4,
		WEST = 5,
		NORTHWEST = 6,
		NORTH = 7
	};

	Personagem(float rowActual, float colActual, float offsetx, float offsety, TileSet tileSet)
	{
		this->rowActual = rowActual;
		this->colActual = colActual;
		this->offsetx = offsetx;
		this->offsety = offsety;
		this->tileSet = tileSet;
		this->anterior = -1;
	}

	void novo(float rowActual, float colActual, float offsetx, float offsety, TileSet tileSet)
	{
		this->rowActual = rowActual;
		this->colActual = colActual;
		this->offsetx = offsetx;
		this->offsety = offsety;
		this->tileSet = tileSet;
		this->anterior = -1;
	}

};

#endif