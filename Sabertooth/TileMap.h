#ifndef TILEMAP_H
#define TILEMAP_H

#include "TileSet.h"

class TileMap
{
public:
	
	char unsigned ** idTiles;
	int tiles_new[10][10];

	int numLinhas;
	int numColunas;
	TileSet tileset;
	int TH;
	int TH_CENTRO;
	int TW;
	int TW_CENTRO;

	TileMap() {}
	~TileMap() {}

	TileMap (char* filePath, int numLinhas, int numColunas, TileSet tileset, int tile_height)
	{
		this->idTiles = new char unsigned*[numLinhas];

		for (int i = 0; i < numLinhas; i++) {
			this->idTiles[i] = new char unsigned[numColunas];
		}

		std::ifstream file(filePath);
		std::string line;

		int i = numLinhas - 1, j = 0;
		while (getline(file, line, ',')) {
			this->idTiles[i][j] = stoi(line);
			this->tiles_new[i][j] = stoi(line);
			j++;
			//printf("%c - %d", this->idTiles[i][j], stoi(line));
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

	void novo(char* filePath, int numLinhas, int numColunas, TileSet tileset, int tile_height)
	{
		this->idTiles = new char unsigned*[numLinhas];

		for (int i = 0; i < numLinhas; i++) {
			this->idTiles[i] = new char unsigned[numColunas];
		}

		std::ifstream file(filePath);
		std::string line;

		int i = numLinhas - 1, j = 0;
		while (getline(file, line, ',')) {
			this->idTiles[i][j] = stoi(line);
			this->tiles_new[i][j] = stoi(line);
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

		int idTile = (float) this->tiles_new[i][j];

		float x = (float) (idTile % this->tileset.numColunas) / tileset.numColunas;
		float y = 0;
		if (idTile >= tileset.numColunas) {
			y = 0.5f;
		}

		printf("%f -- %f \n\n", x, y);
		float offsets[2] = {x, y};

		return offsets;
	}
}; 

#endif