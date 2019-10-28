#ifndef TILEMAP_H
#define TILEMAP_H

#include "TileSet.h"

#include <fstream>
#include <string>

class TileMap
{
public:
	
	char unsigned ** idTiles;

	int numLinhas;
	int numColunas;
	TileSet tileset;
	int TH;
	int TH_CENTRO;
	int TW;
	int TW_CENTRO;

	TileMap (char* filePath, int numLinhas, int numColunas, TileSet tileset, int tile_height)
	{
		this->idTiles = new char unsigned*[numLinhas];

		for (int i = 0; i < numLinhas; i++) {
			this->idTiles[i] = new char unsigned[numColunas];
		}

		std::ifstream file(filePath);
		std::string line = "";

		int i = numLinhas - 1, j = 0;
		while (getline(file, line, ',')) {
			this->idTiles[i][j] = stoi(line);
			j++;

			if (j == numColunas) {
				i--;
				j = 0;
			}
		}

		this->numColunas = numColunas;
		this->numLinhas = numLinhas;
		this->tileset = tileset;
		this->TH = tile_height;
		this->TH_CENTRO = TH / 2;
		this->TW = 2 * TH;
		this->TW_CENTRO = TW / 2;
	}

	float* TileMap::GetTileOffset(int i, int j)
	{
		if (i < 0 || i >= numLinhas || j < 0 || j >= numColunas) {
			return {};
		}

		char unsigned idTile = this->idTiles[i][j];

		float offsets[2] = {
			idTile % this->tileset.numColunas,
			idTile / this->tileset.numColunas
		};

		return offsets;
	}
}; 

#endif