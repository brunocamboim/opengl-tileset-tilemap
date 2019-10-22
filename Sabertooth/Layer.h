#include <GL/glew.h>
#include <SOIL.h>

using namespace std;

// Classe que carrega imagens (textura do mapa).
class Layer
{
public:

	GLuint texture;
	float offsetx;
	float offsety;
	float x;
	float y;
	float z;
	float ratex;
	float prop;

	virtual void loadTexture(char* filepath);
};

