#include "System.h"

#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TileMap.h"
#include "TileSet.h"
#include "Diamond.h"

#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int const TH = 40.0f;
int const TH_CENTRO = TH / 2;
int const TW = 2 * TH;
int const TW_CENTRO = TW / 2;

float const NUM_COLUNAS = 10;
float const NUM_LINHAS = 10;

float TELA_LARGURA = TW * NUM_COLUNAS;
float TELA_ALTURA = TH * NUM_COLUNAS;

glm::mat4 matrix_origem = glm::mat4(1);
Diamond diamond;
TileMap tileMap;
TileSet tileSet;

void mouse_callback(GLFWwindow * window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			double mx, my;
			glfwGetCursorPos(window, &mx, &my);


			double r, c, x0, y0;

			r = my / tileMap.TH_CENTRO;
			c = (mx - r * (tileMap.TW_CENTRO / 2)) / tileMap.TW;
			printf("%f - %f\n\n", r, c);

			/*col = ((2.0f * mx / tileMap.TW) + (2.0f * my / tileMap.TH)) / 2.0f;
			row = (my / tileMap.TH + col);*/
			//x0 = col * this->background_map.TW_CENTRO + row * this->background_map.TW_CENTRO;
			//y0 = (col * this->background_map.TH_CENTRO - row * this->background_map.TH_CENTRO) + ((double)this->background_map.numLinhas * (double)this->background_map.TH_CENTRO) - this->background_map.TH_CENTRO;

		}
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
{
	if (key == GLFW_KEY_LEFT)
	{
		
	}
	else if (key == GLFW_KEY_RIGHT)
	{
		
	}
	else if (key == GLFW_KEY_SPACE)
	{

	}
}


int main() {
	

	if (!glfwInit()) {
		//fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}
	/* Caso necessário, definições específicas para SOs, p. e. Apple OSX *
	/* Definir como 3.2 para Apple OS X */
	/*glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
	GLFWwindow *g_window = glfwCreateWindow(
		640, 480, "Teste de versão OpenGL", NULL, NULL);
	if (!g_window) {
		//fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(g_window);
	// inicia manipulador da extensão GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	float A[] = { 0 , TH / 2 };
	float B[] = { TW / 2, TH };
	float C[] = { TW , TH / 2 };
	float D[] = { TW / 2, 0 };

	float AT[] = { 0.0f, 0.5f };
	float BT[] = { 0.5f, 1.0f };
	float CT[] = { 1.0f, 0.5f };
	float DT[] = { 0.5f, 0.0f };

	int moveX = 0;
	int moveY = 0;

	float vertices[] = {
		// Posicoes		// Textura	
		A[0] + moveX, A[1] + moveY, 0.0f,	AT[0], AT[1],	// A
		B[0] + moveX, B[1] + moveY, 0.0f,	BT[0], BT[1],	// B
		C[0] + moveX, C[1] + moveY, 0.0f,	CT[0], CT[1],	// C
		D[0] + moveX, D[1] + moveY, 0.0f,	DT[0], DT[1],	// D
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute		                //de quanto em quanto	//onde começa
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	const char* vertex_shader =
		"#version 410\n"
		"layout (location = 0) in vec2 vertex_position;"
		"layout (location = 1) in vec2 texture_mapping;"
		"out vec2 texture_coords;"
		
		"uniform mat4 matrix;"
		"uniform mat4 proj;"
		
		"void main () {"
			"texture_coords = texture_mapping;"
			"gl_Position = proj * matrix * vec4(vertex_position, 0.0f, 1.0f);"
		"}";

	const char* fragment_shader =
		"#version 410\n"
		"in vec2 texture_coords;"

		"uniform sampler2D sprite;"
		"uniform float offsetx;"
		"uniform float offsety;"
		"uniform float x;"
		"uniform float y;"

		"out vec4 frag_color;"

		"void main () {"
			"vec2 tc = vec2((texture_coords.x + offsetx), (texture_coords.y + offsety));"
			"frag_color = texture(sprite, tc);"
			/*"vec4 texel = texture (sprite, vec2((texture_coords.x + offsetx) * imagem, texture_coords.y + offsety));"
			"if (texel.a < 0.5) {"
				"discard;"
			"}"
			"frag_color = texel;"*/
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	// identifica fs e o associa com fragment_shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	// identifica do programa, adiciona partes e faz "linkagem"
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	glUseProgram(shader_programme);

	glfwSetMouseButtonCallback(g_window, mouse_callback);
	glfwSetKeyCallback(g_window, key_callback);

	glm::mat4 proj = glm::ortho(0.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(
		glGetUniformLocation(shader_programme, "proj"), 1,
		GL_FALSE, glm::value_ptr(proj));


	tileSet.novo("bin/Images/tileset.png", 0.1f, 0.1f, 2, 5, TH, TW);
	tileMap.novo("bin/Images/tilemap.csv", NUM_LINHAS, NUM_COLUNAS, tileSet, TH);

	/*printf("%f - %f - %d - %d - %f - %f\n", 
		tileSet.x, tileSet.y, tileSet.numColunas, tileSet.numLinhas, tileSet.alturaTiles, tileSet.larguraTiles);

	printf("%d - %d - %d - %d - %d - %d\n",
		tileMap.numLinhas, tileMap.numColunas, tileMap.TH, tileMap.TH_CENTRO, tileMap.TW, tileMap.TW_CENTRO);*/

	/*for (int r = 0; r < tileMap.numLinhas; r++)
	{
		for (int c = tileMap.numColunas - 1; c >= 0; c--)
		{
			printf("%d \n", tileMap.idTiles[r][c]);
		}
	}*/

	diamond.novo(shader_programme, tileMap);

	glm::mat4 matrix_aux = glm::translate(glm::mat4(1), glm::vec3(20, 40, 0.0f));

	bool teste = false;
	while (!glfwWindowShouldClose(g_window))
	{
		processInput(g_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(shader_programme);

		glBindVertexArray(VAO);
		
		for (int r = 0; r < tileMap.numLinhas; r++)
		{
			for (int c = tileMap.numColunas - 1; c >= 0; c--)
			{

				float* offsets = tileMap.GetTileOffset(r, c);

				diamond.desenhar(r, c, tileSet, 0, 0);

			}
		}


		////GL_POSITION
		//float tx = j * tileMap.TW_CENTRO + i * tileMap.TW_CENTRO;
		//float ty = j * tileMap.TH_CENTRO - i * tileMap.TH_CENTRO;

		////TEXTURE
		//float CT = offsets[0];
		//float RT = offsets[1];

		//float TTW = 0;
		//float TTH = 0;
		//float sx = CT * TTW;
		//float sy = RT * TTH;

		//glm::mat4 transformation = glm::translate(
		//	matrix_origem,
		//	glm::vec3(
		//		//j * tileMap.TW_CENTRO + i * tileMap.TW_CENTRO,
		//		0.0f,
		//		0.0f,
		//		0.0f
		//	)
		//);

		glfwSwapBuffers(g_window);
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}