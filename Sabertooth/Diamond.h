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

	Diamond(GLuint shader_programme, TileMap background_map)
	{
		this->matrix = glm::mat4(1);
		this->matrix_origem = glm::mat4(1);
		this->shader_programme = shader_programme;
		this->background_map = background_map;
	}

	void desenhar(float i, float j, TileSet tileset, float offsetx, float offsety)
	{
		/*glm::mat4 transformation = glm::translate(
			matrix_origem, 
			glm::vec3(j * this->background_map.TW_CENTRO + i * this->background_map.TW_CENTRO, 
				(j * this->background_map.TH_CENTRO - i * this->background_map.TH_CENTRO) 
				+ 
				(this->background_map.numLinhas * this->background_map.TH_CENTRO) 
				+ 
				this->background_map.TH_CENTRO - tileset.alturaTiles, 
			0.0f));*/

		this->matrix = matrix_origem;

		glUniformMatrix4fv(
			glGetUniformLocation(this->shader_programme, "matrix"), 1,
			GL_FALSE, glm::value_ptr(this->matrix));

		glUniform1f(
			glGetUniformLocation(shader_programme, "tamanho"), 1);

		glUniform1f(
			glGetUniformLocation(shader_programme, "offsetx"), offsetx);
		glUniform1f(
			glGetUniformLocation(shader_programme, "offsety"), offsety);

		// bind Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tileset.GetTextureID());
		glUniform1i(glGetUniformLocation(this->shader_programme, "sprite"), 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

};

