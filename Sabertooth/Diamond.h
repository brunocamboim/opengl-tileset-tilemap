#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h> /* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h>

#include "TileMap.h"

// Classe utilizada para criar o formato diamante no jogo.
class Diamond
{
public:

	GLuint shader_programme;
	glm::mat4 matrix;
	glm::mat4 matrix_origem;
	TileMap background_map;
	int numLifes;
	bool game_win;
	bool game_over;

	Diamond() {}
	~Diamond() {}

	Diamond(GLuint shader_programme, TileMap background_map)
	{
		this->matrix = glm::mat4(1);
		this->matrix_origem = glm::mat4(1);
		this->shader_programme = shader_programme;
		this->background_map = background_map;
		this->game_win = false;
		this->game_over = false;
		this->numLifes = 3;
	}

	void novo(GLuint shader_programme, TileMap background_map)
	{
		this->matrix = glm::mat4(1);
		this->matrix_origem = glm::mat4(1);
		this->shader_programme = shader_programme;
		this->background_map = background_map;
		this->game_win = false;
		this->game_over = false;
		this->numLifes = 3;
	}

	void desenhar(float r, float c, TileSet tileSet, float offsetx, float offsety)
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

		// bind Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tileSet.GetTextureID());
		glUniform1i(glGetUniformLocation(this->shader_programme, "sprite"), 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
};

