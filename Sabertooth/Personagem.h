#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include "TileSet.h"

class Personagem
{
public:
	Personagem() {}
	~Personagem() {}

	float rowActual;
	float colActual;
	float offsetx;
	float offsety;
	TileSet tileSet;

	Personagem(float rowActual, float colActual, float offsetx, float offsety, TileSet tileSet)
	{
		this->rowActual = rowActual;
		this->colActual = colActual;
		this->offsetx = offsetx;
		this->offsety = offsety;
		this->tileSet = tileSet;
	}

	void novo(float rowActual, float colActual, float offsetx, float offsety, TileSet tileSet)
	{
		this->rowActual = rowActual;
		this->colActual = colActual;
		this->offsetx = offsetx;
		this->offsety = offsety;
		this->tileSet = tileSet;
	}
};

#endif