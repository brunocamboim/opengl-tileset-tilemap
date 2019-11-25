#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h> /* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h>

#include "TileMap.h"
#include "Personagem.h"

// Classe utilizada para criar o formato diamante no jogo.
class Diamond
{
public:

	GLuint shader_programme;
	glm::mat4 matrix;
	glm::mat4 matrix_origem;
	TileMap background_map;
	TileSet tileSetLife;
	int numLifes;
	bool game_win;
	bool game_over;
	int points;
	

	Diamond() {}
	~Diamond() {}

	Diamond(GLuint shader_programme, TileMap background_map, TileSet tileSetLife)
	{
		this->matrix = glm::mat4(1);
		this->matrix_origem = glm::mat4(1);
		this->shader_programme = shader_programme;
		this->background_map = background_map;
		this->tileSetLife = tileSetLife;
		this->game_win = false;
		this->game_over = false;
		this->numLifes = 3;
		this->points = 0;
	}

	void novo(GLuint shader_programme, TileMap background_map, TileSet tileSetLife)
	{
		this->matrix = glm::mat4(1);
		this->matrix_origem = glm::mat4(1);
		this->shader_programme = shader_programme;
		this->background_map = background_map;
		this->tileSetLife = tileSetLife;
		this->game_win = false;
		this->game_over = false;
		this->numLifes = 3;
		this->points = 0;
	}

	int clique(double linha, double coluna, Personagem personagem) {
		

		int pegouBola;
		if (linha > 60 && linha < 130 && coluna > 150 && coluna < 175 && personagem.colActual < 2 && personagem.rowActual < 2) {
			pegouBola = 1;			
		}
		else {
			pegouBola = 0;
		}
		
		
		return pegouBola;
		

	}

	/*bool pegouBola() {
		if(pegouBola==0)
			return false;
		return true;
	}*/

	void desenhar(float r, float c, TileSet tileSet, float offsetx, float offsety, float tamanho = 1)
	{
		//translação do tile (em x e y baseado em c e r)
		float x = c * tileSet.larguraTiles / 2 + r * tileSet.larguraTiles / 2;
		float y = c * tileSet.alturaTiles / 2 - r * tileSet.alturaTiles / 2;
		y = y + (this->background_map.numLinhas * this->background_map.TH_CENTRO) + (this->background_map.TH_CENTRO - tileSet.alturaTiles);
		this->matrix_origem = glm::translate(glm::mat4(1), glm::vec3(x, y, 0.0f));

		glUniformMatrix4fv(
			glGetUniformLocation(this->shader_programme, "matrix"), 1,
			GL_FALSE, glm::value_ptr(matrix_origem));

		glUniform1f(
			glGetUniformLocation(this->shader_programme, "offsetx"), offsetx);
		glUniform1f(
			glGetUniformLocation(this->shader_programme, "offsety"), offsety);

		glUniform1f(
			glGetUniformLocation(this->shader_programme, "tamanho"), tamanho);

		// bind Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tileSet.GetTextureID());
		glUniform1i(glGetUniformLocation(this->shader_programme, "sprite"), 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void desenharVida() {

		float numsY[] = {
			2.5f,
			3.5f,
			4.5f
		};
		for (int i = 0; i < this->numLifes; i++) {
			desenhar(11.5f, numsY[i], this->tileSetLife, 0, 0, 0.5f);
		}
	}

	void tileWalking(float& c, float& r, int direction, float qtd)
	{
		switch (direction)
		{
		case 0: //NORTHEAST:
			c = c + qtd;
			break;
		case 1: //EAST
			c = c + qtd;
			r = r + qtd;
			break;
		case 2: //SOUTHEAST
			r = r + qtd;
			break;
		case 3: //SOUTH
			c = c - qtd;
			r = r + qtd;
			break;
		case 4: //SOUTHWEST
			c = c - qtd;
			break;
		case 5: //WEST
			c = c - qtd;
			r = r - qtd;
			break;
		case 6: //NORTHWEST
			r = r - qtd;
			break;
		case 7: //NORTH
			c = c + qtd;
			r = r - qtd;
			break;
		}
	}

	bool checkCharactersColision(Personagem personagem, Personagem inimigo)
	{

		inimigo.rowActual = inimigo.rowActual - 0.1f;
		inimigo.colActual = inimigo.colActual - 0.1f;
		return round(inimigo.rowActual) == round(personagem.rowActual) && round(inimigo.colActual) == round(personagem.colActual);
	}

	void restart(Personagem& personagem, Personagem *inimigos) {
		if (this->points >= 3) {
			this->game_win = true;
		}


		inimigos[0].rowActual = 7;
		inimigos[1].rowActual = 5;
		inimigos[2].rowActual = 5;
		inimigos[3].rowActual = 2;
		inimigos[4].rowActual = 9;
		inimigos[5].rowActual = 9;

		inimigos[0].colActual = 7;
		inimigos[1].colActual = 5;
		inimigos[2].colActual = 5;
		inimigos[3].colActual = 1;
		inimigos[4].colActual = 0;
		inimigos[5].colActual = 9;

		inimigos[0].movimento = 0;
		inimigos[1].movimento = 1;
		inimigos[2].movimento = 2;
		inimigos[3].movimento = 3;
		inimigos[4].movimento = 3;
		inimigos[5].movimento = 3;

		inimigos[0].offsetx = 1;
		inimigos[1].offsetx = 1;
		inimigos[2].offsetx = 1;
		inimigos[3].offsetx = 1;
		inimigos[4].offsetx = 1;
		inimigos[5].offsetx = 1;

		inimigos[0].offsety = 1;
		inimigos[1].offsety = 1;
		inimigos[2].offsety = 1;
		inimigos[3].offsety = 1;
		inimigos[4].offsety = 1;
		inimigos[5].offsety = 1;

		personagem.rowActual = 1;
		personagem.colActual = 8;
	}

};

