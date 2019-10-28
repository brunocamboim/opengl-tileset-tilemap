#ifndef LAYER_H
#define LAYER_H

#include <GL/glew.h> /* include GLEW and new version of GL on Windows */
#include <stdio.h>
#include <stdlib.h>
#include <SOIL.h>

using namespace std;

// Classe que carrega imagens (textura do mapa).
class Layer
{
public:
	Layer();
	~Layer();

	GLuint texture;
	float offsetx;
	float offsety;
	float x;
	float y;
	float z;
	float ratex;
	float prop;

	void loadTexture(char* filepath);
};
#endif
