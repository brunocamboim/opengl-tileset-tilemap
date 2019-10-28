#ifndef TILESET_H
#define TILESET_H

#include "Layer.h"
// Classe responsável por criar o TileSet.
class TileSet
{
public:

	Layer texture;
	char* filePath;
	float x;
	float y;
	int numColunas;
	int numLinhas;
	float alturaTiles;
	float larguraTiles;

	TileSet() {}
	~TileSet() {}

	TileSet (char* filePath, float x, float y, int numColunas, int numLinhas, float alturaTiles, float larguraTiles)
	{
		this->texture.loadTexture(filePath);
		this->x = x;
		this->y = y;
		this->numColunas = numColunas;
		this->numLinhas = numLinhas;
		this->alturaTiles = alturaTiles;
		this->larguraTiles = larguraTiles;
	}

	int TileSet::GetTextureID()
	{
		return this->texture.texture;
	}

};

#endif