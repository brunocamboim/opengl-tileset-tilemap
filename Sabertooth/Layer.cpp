#include "Layer.h"



Layer::Layer()
{
}


Layer::~Layer()
{
}
//  Carrega a textura 
void Layer::loadTexture(char* filepath)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST ou GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST ou GL_LINEAR);

	// load and generate the texture
	int width, height;
	unsigned char* data = SOIL_load_image(filepath, &width, &height, 0, SOIL_LOAD_RGBA);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("%s: %s", "Failed to load texture", filepath);
	}
	SOIL_free_image_data(data);
}
