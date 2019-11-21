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
TileSet tileSet;
TileSet tileSet2;
TileSet inimigo;
Personagem personagem;

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

	float AT[] = { 0.0f, 0.25f };
	float BT[] = { 0.1f, 0.5f };
	float CT[] = { 0.2f, 0.25f };
	float DT[] = { 0.1f, 0.0f };

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
			"vec4 texel = texture(sprite, tc);"
			/*"vec4 texel = texture (sprite, vec2((texture_coords.x + offsetx) * imagem, texture_coords.y + offsety));"*/
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

	tileSet2.novo("bin/Images/personagem.png", 0.5f, 0.5f, 5, 2, TH, TW);

	inimigo.novo("bin/Images/inimigo.png", 0.5f, 0.5f, 5, 2, TH, TW);

	//TileSet tileSetPersonagem("bin/Images/personagem.png", 0.1f, 0.1f, 5, 2, TH, TW);
	//personagem.novo(5, 5, 0, 0, tileSetPersonagem);

	/*printf("%f - %f - %d - %d - %f - %f\n", 
		tileSet.x, tileSet.y, tileSet.numColunas, tileSet.numLinhas, tileSet.alturaTiles, tileSet.larguraTiles);

	printf("%d - %d - %d - %d - %d - %d\n",
		tileMap.numLinhas, tileMap.numColunas, tileMap.TH, tileMap.TH_CENTRO, tileMap.TW, tileMap.TW_CENTRO);*/

	/*for (int r = 0; r < tileMap.numLinhas; r++)
	{
		for (int c = tileMap.numColunas - 1; c >= 0; c--)
		{
			printf("%d \n", tileMap.tiles_new[r][c]);
		}
	}*/
	

	diamond.novo(shader_programme, tileMap);

	glm::mat4 matrix_aux = glm::translate(glm::mat4(1), glm::vec3(20, 40, 0.0f));

	bool teste = false;

	double movimentoX=1;
	double movimentoY=8;

	
	

	double limiteEsquerdaSuperior=9.2;
	double limiteEsquerdaInferior=8.5;
	double limiteDireitaSuperior=0;
	double limiteDireitaInferior=0.4;

	float linhaInimigo[4];
	linhaInimigo[0] = 7;
	linhaInimigo[1] = 5;
	linhaInimigo[2] = 5;
	linhaInimigo[3] = 8;

	float colunaInimigo[4];
	colunaInimigo[0] = 7;
	colunaInimigo[1] = 5;
	colunaInimigo[2] = 5;
	colunaInimigo[3] = 2;

	
	int movimentoInimigo[4];
	//0=linha
	movimentoInimigo[0] = 0;
	//1=coluna
	movimentoInimigo[1] = 1;
	//2=linhaColuna
	movimentoInimigo[2] = 2;
	//3=persegueJogador
	movimentoInimigo[3] = 3;


	float anteriorInimigo[4];
	anteriorInimigo[0] = -1;
	anteriorInimigo[1] = -1;
	anteriorInimigo[2] = 1;
	anteriorInimigo[3] = -1;
	


	
	while (!glfwWindowShouldClose(g_window))
	{
		processInput(g_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(shader_programme);

		glBindVertexArray(VAO);

		//diamond.desenhar(personagem.rowActual, personagem.colActual, personagem.tileSet, personagem.offsetx, personagem.offsety);
		
		for (int r = 0; r < tileMap.numLinhas; r++)
		{
			for (int c = tileMap.numColunas - 1; c >= 0; c--)
			{

				float* offsets = tileMap.GetTileOffset(r, c);
				//if (!teste) printf("%f - %f \n", offsets[0], offsets[1]);

				diamond.desenhar(r, c, tileSet, offsets[0], offsets[1]);
				//diamond.desenhar(r, c, tileSet, 0, 0.5);

			}
		}


		
		int stateD = glfwGetKey(g_window, GLFW_KEY_D);
		int stateW = glfwGetKey(g_window, GLFW_KEY_W);
		int stateA = glfwGetKey(g_window, GLFW_KEY_A);
		int stateS = glfwGetKey(g_window, GLFW_KEY_S);

		if (stateD == GLFW_PRESS) {
			if (stateW == GLFW_PRESS && movimentoX < limiteEsquerdaSuperior) {
				movimentoX += 0.015;
			}
			else if (stateS == GLFW_PRESS && movimentoY < limiteEsquerdaInferior) {
				movimentoY += 0.015;
			}
			else if (movimentoX < limiteEsquerdaSuperior && movimentoY < limiteEsquerdaInferior){
				movimentoX += 0.015;
				movimentoY += 0.015;
			}
		}
		else if (stateW == GLFW_PRESS) {
			if (stateA == GLFW_PRESS && movimentoY > limiteDireitaSuperior) {
				movimentoY -= 0.015;
			}
			else if (stateD == GLFW_PRESS && movimentoX < limiteEsquerdaSuperior) {
				movimentoX += 0.015;
			}
			else if(movimentoY > limiteDireitaSuperior && movimentoX < limiteEsquerdaSuperior){
				movimentoX += 0.015;
				movimentoY -= 0.015;
			}
			

		}
		else if (stateA == GLFW_PRESS) {
			if (stateW == GLFW_PRESS && movimentoY > limiteDireitaSuperior) {
				movimentoY -= 0.015;
			}
			else if (stateS == GLFW_PRESS && movimentoX > limiteDireitaInferior) {
				movimentoX -= 0.015;
			}
			else if (movimentoY > limiteDireitaSuperior && movimentoX > limiteDireitaInferior){
				movimentoX -= 0.015;
				movimentoY -= 0.015;
			}
			

		}
		else if (stateS == GLFW_PRESS) {
			if (stateA == GLFW_PRESS && movimentoX > limiteDireitaInferior) {
				movimentoY += 0.015;
			}
			else if (stateD == GLFW_PRESS && movimentoY < limiteEsquerdaInferior) {
				movimentoX -= 0.015;
			}
			else if (movimentoX > limiteDireitaInferior && movimentoY < limiteEsquerdaInferior){
				movimentoX -= 0.015;
				movimentoY += 0.015;
			}
			

		}
		diamond.desenhar(movimentoX, movimentoY, tileSet2, 1, 1);

		for (int i = 0; i < 4; i++) {			
			if (movimentoInimigo[i] == 0) {				
				if (linhaInimigo[i] < limiteEsquerdaSuperior && anteriorInimigo[i]>0) {					
					linhaInimigo[i] += 0.015;					
				}
				else {
					anteriorInimigo[i] = -1;
				}
				if (linhaInimigo[i] > limiteDireitaInferior && anteriorInimigo[i]<0) {
					linhaInimigo[i] -= 0.015;
				}
				else {
					anteriorInimigo[i] = 1;
				}
			}
			else if (movimentoInimigo[i] == 1) {
				if (colunaInimigo[i] < limiteEsquerdaInferior && anteriorInimigo[i]>0) {
					colunaInimigo[i] += 0.015;
				}
				else {
					anteriorInimigo[i] = -1;
				}
				if (colunaInimigo[i] > limiteDireitaSuperior && anteriorInimigo[i] < 0) {
					colunaInimigo[i] -= 0.015;
				}
				else {
					anteriorInimigo[i] = 1;
				}
			}
			else if (movimentoInimigo[i] == 2) {
				if (linhaInimigo[i] < limiteEsquerdaSuperior && colunaInimigo[i] < limiteEsquerdaInferior && anteriorInimigo[i]>0) {
					linhaInimigo[i] += 0.015;
					colunaInimigo[i] += 0.015;
				}				
				else {
					anteriorInimigo[i] = -1;
				}
				if (linhaInimigo[i] > limiteDireitaSuperior && colunaInimigo[i] > limiteDireitaSuperior && anteriorInimigo[i] < 0) {
					linhaInimigo[i] -= 0.015;
					colunaInimigo[i] -= 0.015;
				}
				else {
					anteriorInimigo[i] = 1;
				}
			}
			/*
			else if (movimentoInimigo[i] == 3) {
				if (linhaInimigo[i] < movimentoX) {
					linhaInimigo[i] += 0.010;
					
				}
				else {
					linhaInimigo[i] += 0.010;
				}
				if (colunaInimigo[i] < movimentoY) {
					
					colunaInimigo[i] += 0.010;
				}
				else {
					colunaInimigo[i] += 0.010;
				}
			}
			*/

			diamond.desenhar(linhaInimigo[i], colunaInimigo[i], inimigo, 1, 1);
		}
		

		teste = true;

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