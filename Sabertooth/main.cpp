#include "System.h"

#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TileMap.h"
#include "TileSet.h"
#include "Diamond.h"
#include "Personagem.h"

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
TileMap tileMapColision;
TileSet tileSet;
TileSet tileSetPersonagem;
TileSet tileSetPersonagemBola;
TileSet inimigo;
TileSet bola;
TileSet tileSetLifes;
Personagem personagem;
Personagem inimigos[4];

int pegouBola;

enum Directions {
	null = -1,
	NORTHEAST = 0,
	EAST = 1,
	SOUTHEAST = 2,
	SOUTH = 3,
	SOUTHWEST = 4,
	WEST = 5,
	NORTHWEST = 6,
	NORTH = 7
};

Directions direction = null;

void mouse_callback(GLFWwindow * window, int button, int action, int mods) {
	
	if (action == GLFW_PRESS) {
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			double mx, my;
			glfwGetCursorPos(window, &mx, &my);
			//printf("%f", mx);
			//printf("%f", my);

			pegouBola=diamond.clique(mx, my, personagem);
			


			double r, c, x0, y0;

			r = my / tileMap.TH_CENTRO;
			c = (mx - r * (tileMap.TW_CENTRO / 2)) / tileMap.TW;
			//printf("%f - %f\n\n", r, c);

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

}

int main() {

	if (!glfwInit()) {
		return 1;
	}

	GLFWwindow *g_window = glfwCreateWindow(
		640, 480, "Teste de versão OpenGL", NULL, NULL);
	if (!g_window) {
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

	float AT[] = { 0.0f, 0.25f };
	float BT[] = { 0.1f, 0.5f };
	float CT[] = { 0.2f, 0.25f };
	float DT[] = { 0.1f, 0.0f };

	float vertices[] = {
		// Posicoes		// Textura	
		A[0], A[1], 0.0f,	AT[0], AT[1],	// A
		B[0], B[1], 0.0f,	BT[0], BT[1],	// B
		C[0], C[1], 0.0f,	CT[0], CT[1],	// C
		D[0], D[1], 0.0f,	DT[0], DT[1],	// D
	};

	float vertices1[] = {
		// positions          // colors           // texture coords
		800.0f, 600.0f, 0.0f,   1.0f, 1.0f, // buttom right
		800.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top left
		0.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
		0.0f, 600.0f, 0.0f,   0.0f, 1.0f //top right
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

	// -------- desenhar life ---------
	unsigned int EBO2;
	glGenBuffers(1, &EBO2);

	unsigned int VBO2, VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);

	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute		                //de quanto em quanto	//onde começa
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int EBO3;
	glGenBuffers(1, &EBO3);

	unsigned int VBO3, VAO3;
	glGenVertexArrays(1, &VAO3);
	glBindVertexArray(VAO3);

	glGenBuffers(1, &VBO3);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute		                //de quanto em quanto	//onde começa
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load("bin/Images/game_win.png", &width, &height, &nrChannels, SOIL_LOAD_RGBA);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps

	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data1 = stbi_load("bin/Images/game_over.png", &width, &height, &nrChannels, SOIL_LOAD_RGBA);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data1);

	const char* vertex_shader =
		"#version 410\n"
		"layout (location = 0) in vec2 vertex_position;"
		"layout (location = 1) in vec2 texture_mapping;"
		"out vec2 texture_coords;"
		
		"uniform mat4 matrix;"
		"uniform mat4 proj;"
		"uniform float tamanho;"
		
		"void main () {"
			"texture_coords = texture_mapping;"
			"gl_Position = proj * matrix * vec4(vertex_position, 0.0f, tamanho);"
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
			"vec4 texel = texture(sprite, tc);"
			"if (texel.a < 0.5) {"
				"discard;"
			"}"
			"frag_color = texel;"
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


	tileSet.novo("bin/Images/tileset.png", 0.1f, 0.1f, 5, 2, TH, TW);
	tileMap.novo("bin/Images/tilemap.csv", NUM_LINHAS, NUM_COLUNAS, tileSet, TH);
	tileMapColision.novo("bin/Images/tilemapcolision.csv", NUM_LINHAS, NUM_COLUNAS, tileSet, TH);

	tileSetPersonagem.novo("bin/Images/personagem.png", 0.5f, 0.5f, 5, 2, TH, TW);
	tileSetPersonagemBola.novo("bin/Images/personagemBola.png", 0.5f, 0.5f, 5, 2, TH, TW);
	//personagem.novo(1, 8, 1, 1, diamond.pegouBola ? tileSetPersonagem : tileSetPersonagemBola);
	personagem.novo(1, 8, 1, 1, tileSetPersonagem);


	inimigo.novo("bin/Images/inimigo.png", 0.5f, 0.5f, 5, 2, TH, TW);
	
	bola.novo("bin/Images/bola.png", 0.5f, 0.5f, 5, 2, TH, TW);

	tileSetLifes.novo("bin/Images/life.png", 0.1f, 0.1f, 3, 1, TH, TW);

	diamond.novo(shader_programme, tileMap, tileSetLifes);

	//-------------------- Define dados iniciais para o jogo ---------------

	double limiteEsquerdaSuperior = 9.2;
	double limiteEsquerdaInferior = 8.5;
	double limiteDireitaSuperior = 0;
	double limiteDireitaInferior = 0.4;

	inimigos[0].rowActual = 7;
	inimigos[1].rowActual = 5;
	inimigos[2].rowActual = 5;
	inimigos[3].rowActual = 8;

	inimigos[0].colActual = 7;
	inimigos[1].colActual = 5;
	inimigos[2].colActual = 5;
	inimigos[3].colActual = 2;
	
	inimigos[0].movimento = 0;
	inimigos[1].movimento = 1;
	inimigos[2].movimento = 2;
	inimigos[3].movimento = 3;
	
	double tempoAtual;
	double animacaoPersonagem;
	double animacaoPersonagemContador = glfwGetTime();

	//float velocidadeMovimento = 0.005f;
	//float velocidadeMovimentoSeguidor = 0.002f;

	float velocidadeMovimento = 0.001f;
	float velocidadeMovimentoSeguidor = 0.00005f;

	bool restart = false;

	int cliqueCerto = 0;
	
	while (!glfwWindowShouldClose(g_window))
	{

		processInput(g_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(shader_programme);

		if (restart) {			

			restart = false;
		}

		if (diamond.game_win) {
			glBindVertexArray(VAO2);

			glUniformMatrix4fv(
				glGetUniformLocation(shader_programme, "matrix"), 1,
				GL_FALSE, glm::value_ptr(glm::mat4(1)));

			glUniform1f(
				glGetUniformLocation(shader_programme, "offsetx"), 0);
			glUniform1f(
				glGetUniformLocation(shader_programme, "offsety"), 0);

			glUniform1f(
				glGetUniformLocation(shader_programme, "tamanho"), 1.0f);

			// bind Texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glUniform1i(glGetUniformLocation(shader_programme, "sprite"), 0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		else if (diamond.game_over || diamond.numLifes == 0) {
			glBindVertexArray(VAO3);

			glUniformMatrix4fv(
				glGetUniformLocation(shader_programme, "matrix"), 1,
				GL_FALSE, glm::value_ptr(glm::mat4(1)));

			glUniform1f(
				glGetUniformLocation(shader_programme, "offsetx"), 0);
			glUniform1f(
				glGetUniformLocation(shader_programme, "offsety"), 0);

			glUniform1f(
				glGetUniformLocation(shader_programme, "tamanho"), 1.0f);

			// bind Texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture2);
			glUniform1i(glGetUniformLocation(shader_programme, "sprite"), 0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		


		else {

			glBindVertexArray(VAO);

			diamond.desenharVida();

			for (int r = 0; r < tileMap.numLinhas; r++)
			{
				for (int c = tileMap.numColunas - 1; c >= 0; c--)
				{

					float* offsets = tileMap.GetTileOffset(r, c);
					diamond.desenhar(r, c, tileSet, offsets[0], offsets[1]);

				}
			}

			tempoAtual = glfwGetTime();
			animacaoPersonagem = tempoAtual - animacaoPersonagemContador;

			if(pegouBola==0)
				diamond.desenhar(1, 1, bola, 1, 1);

			if (animacaoPersonagem >= 0.20) {
				animacaoPersonagemContador = glfwGetTime();
				if (personagem.movimento == 0) {
					personagem.movimento = 1;
				}
				else {
					personagem.movimento = 0;
				}
			}

			int stateD = glfwGetKey(g_window, GLFW_KEY_D);
			int stateW = glfwGetKey(g_window, GLFW_KEY_W);
			int stateA = glfwGetKey(g_window, GLFW_KEY_A);
			int stateS = glfwGetKey(g_window, GLFW_KEY_S);

			if (stateW == GLFW_PRESS) {
				if (stateA == GLFW_PRESS) {
					direction = SOUTHWEST;
				}
				else if (stateD == GLFW_PRESS) {
					direction = SOUTHEAST;
				}
				else {
					direction = SOUTH;
				}
				personagem.offsetx = personagem.movimento ? personagem.offsetx = 0.2f : personagem.offsetx = 0;
				personagem.offsety = 0.0f;
			}
			else if (stateS == GLFW_PRESS) {
				if (stateA == GLFW_PRESS) {
					direction = NORTHWEST;
				}
				else if (stateD == GLFW_PRESS) {
					direction = NORTHEAST;
				}
				else {
					direction = NORTH;
				}
				personagem.offsetx = personagem.movimento ? personagem.offsetx = 0.2f : personagem.offsetx = 0;
				personagem.offsety = 0.4f;
			}
			else if (stateD == GLFW_PRESS) {
				direction = EAST;
				personagem.offsetx = personagem.movimento ? personagem.offsetx = 0.8f : personagem.offsetx = 0.6f;
				personagem.offsety = 0.4f;
			}
			else if (stateA == GLFW_PRESS) {
				direction = WEST;
				personagem.offsetx = personagem.movimento ? personagem.offsetx = 0.8f : personagem.offsetx = 0.6f;
				personagem.offsety = 0.0f;
			}
			else {
				direction = null;
				personagem.offsetx = 0;
				personagem.offsety = 0;
			}

			float row = personagem.rowActual;
			float col = personagem.colActual;
			diamond.tileWalking(col, row, direction, velocidadeMovimento);
			bool colision = tileMapColision.checkColision(round(row), round(col));
			if (!colision) {
				personagem.rowActual = row;
				personagem.colActual = col;
			}
			
			diamond.desenhar(personagem.rowActual, personagem.colActual, pegouBola==0 ? tileSetPersonagem : tileSetPersonagemBola, personagem.offsetx, personagem.offsety);

			for (int i = 0; i < 4; i++) {

				switch (inimigos[i].movimento)
				{
				case 0:
					if (inimigos[i].rowActual < limiteEsquerdaSuperior && inimigos[i].anterior > 0) {
						inimigos[i].rowActual += velocidadeMovimento;
					}
					else {
						inimigos[i].anterior = -1;
					}
					if (inimigos[i].rowActual > limiteDireitaInferior && inimigos[i].anterior < 0) {
						inimigos[i].rowActual -= velocidadeMovimento;
					}
					else {
						inimigos[i].anterior = 1;
					}
					break;
				case 1:
					if (inimigos[i].colActual < limiteEsquerdaInferior && inimigos[i].anterior > 0) {
						inimigos[i].colActual += velocidadeMovimento;
					}
					else {
						inimigos[i].anterior = -1;
					}
					if (inimigos[i].colActual > limiteDireitaSuperior && inimigos[i].anterior < 0) {
						inimigos[i].colActual -= velocidadeMovimento;
					}
					else {
						inimigos[i].anterior = 1;
					}
					break;
				case 2:
					if (inimigos[i].rowActual < limiteEsquerdaSuperior && inimigos[i].colActual < limiteEsquerdaInferior && inimigos[i].anterior > 0) {
						inimigos[i].rowActual += velocidadeMovimento;
						inimigos[i].colActual += velocidadeMovimento;
					}
					else {
						inimigos[i].anterior = -1;
					}
					if (inimigos[i].rowActual > limiteDireitaSuperior && inimigos[i].colActual > limiteDireitaSuperior && inimigos[i].anterior < 0) {
						inimigos[i].rowActual -= velocidadeMovimento;
						inimigos[i].colActual -= velocidadeMovimento;
					}
					else {
						inimigos[i].anterior = 1;
					}
					break;
				case 3:
					if (inimigos[i].rowActual < personagem.rowActual) {
						inimigos[i].rowActual += velocidadeMovimentoSeguidor;

					}
					else if (inimigos[i].rowActual > personagem.rowActual) {
						inimigos[i].rowActual -= velocidadeMovimentoSeguidor;
					}
					if (inimigos[i].colActual < personagem.colActual) {
						inimigos[i].colActual += velocidadeMovimentoSeguidor;
					}
					else if (inimigos[i].colActual > personagem.colActual) {
						inimigos[i].colActual -= velocidadeMovimentoSeguidor;
					}
					break;
				}
				diamond.desenhar(inimigos[i].rowActual, inimigos[i].colActual, inimigo, 1, 1);

				if (diamond.checkCharactersColision(personagem, inimigos[i])) {
					diamond.numLifes--;
					diamond.restart(personagem, inimigos);
					pegouBola = 0;
				}


				
			}

			
		}
		
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