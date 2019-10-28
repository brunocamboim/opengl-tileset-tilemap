#include "System.h"

#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TileMap.h"
#include "TileSet.h"

#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::mat4 matrix_origem = glm::mat4(1);

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

	float vertices[] = {
		// positions          // colors           // texture coords
		0.0f, 480.0f, 0.0f,   1.0f, 1.0f, // buttom right
		0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top left
		640.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
		640.0f, 480.0f, 0.0f,   0.0f, 1.0f //top right
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
		"uniform float layer_z;"
		"uniform float tamanho;"
		
		"void main () {"
			"texture_coords = texture_mapping;"
			"gl_Position = proj * matrix * vec4(vertex_position, layer_z, tamanho);"
		"}";

	const char* fragment_shader =
		"#version 410\n"
		"in vec2 texture_coords;"

		"uniform sampler2D sprite;"
		"uniform float offsetx;"
		"uniform float offsety;"
		"uniform float imagem;"

		"out vec4 frag_color;"

		"void main () {"
			"vec4 texel = texture (sprite, vec2((texture_coords.x + offsetx), texture_coords.y + offsety));"
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


	unsigned int texture1;
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
	unsigned char *data = stbi_load("bin/Images/wall.png", &width, &height, &nrChannels, SOIL_LOAD_RGBA);
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

	glUseProgram(shader_programme);
	glfwSetKeyCallback(g_window, key_callback);

	glUniform1i(glGetUniformLocation(shader_programme, "texture1"), 0);

	//int matrixLocation = glGetUniformLocation(shader_programme, "matrix");
	//glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);
	
	glm::mat4 proj = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(
		glGetUniformLocation(shader_programme, "proj"), 1,
		GL_FALSE, glm::value_ptr(proj));

	
	
	TileSet tileSet("bin/Images/wall.png", 0.1f, 0.1f, 10, 58, 154.0f, 77.0f);
	TileMap tileMap("bin/Images/tilemap.csv", 10, 10, tileSet, 32);

	//tileSetCenario = TileSet::TileSet("bin/Images/wall.png", 0.1f, 0.1f, 10, 58, 154.0f, 77.0f);
	//TileMap tilemapCenario("bin/Images/tilemap.csv", 10, 10, tileSetCenario, 32);

	//tileSetCenario = TileSet::TileSet("bin/Images/wall.png", 0.1f, 0.1f, 10, 58, 154.0f, 77.0f);
	//TileMap::TileMap("bin/Images/tilemap.csv", 10, 10, tileSetCenario, 32);

	float speed = 1.0f;
	float lastPosition = 0.0f;

	float layers[1];
	layers[0] = texture1;

	float layersZ[1];
	layersZ[0] = -0.50;

	float vao[1];
	vao[0] = VAO;

	while (!glfwWindowShouldClose(g_window))
	{
		processInput(g_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		static float previousSeconds = glfwGetTime();
		float currentSeconds = glfwGetTime();
		float elapsedSeconds =
			currentSeconds - previousSeconds;
		previousSeconds = currentSeconds;
		
		glUseProgram(shader_programme);


		glBindVertexArray(vao[0]);

		float* offsets;
		for (int i = 0; i < tileMap.numLinhas; i++)
		{
			for (int j = tileMap.numColunas - 1; j >= 0; j--)
			{
				//translação do tile (em x e y baseado em c e r) 
				offsets = tileMap.GetTileOffset(i, j);

				glm::mat4 transformation = glm::translate(
					matrix_origem,
					glm::vec3(
						j * tileMap.TW_CENTRO + i * tileMap.TW_CENTRO,
						(j * tileMap.TH_CENTRO - i * tileMap.TH_CENTRO) + (tileMap.numLinhas * tileMap.TH_CENTRO) + tileMap.TH_CENTRO - tileSet.alturaTiles, 
						0.0f
					)
				);

				//GL_POSITION
				float tx = j * tileMap.TW;
				float ty = i * tileMap.TH;

				//TEXTURE
				float CT = offsets[0];
				float RT = offsets[1];

				float TTW = 0;
				float TTH = 0;
				float sx = CT * TTW;
				float sy = RT * TTH;


				glUniformMatrix4fv(
					glGetUniformLocation(shader_programme, "matrix"), 1,
					GL_FALSE, glm::value_ptr(glm::mat4(1)));
				glUniform1f(
					glGetUniformLocation(shader_programme, "x"), tileSet.x);
				glUniform1f(
					glGetUniformLocation(shader_programme, "y"), tileSet.y);
				glUniform1f(
					glGetUniformLocation(shader_programme, "offsetx"), CT);
				glUniform1f(
					glGetUniformLocation(shader_programme, "offsety"), RT);

				// bind Texture
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tileSet.GetTextureID());
				glUniform1i(glGetUniformLocation(shader_programme, "sprite"), 0);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				
			}
		}

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 8; c++) {
				//translação do tile (em x e y baseado em c e r) 
				//vertex shader:
				//tx = c * tw
				//ty = r * th
				
				//coluna textura e linhas textura
				//define coordenadas x e y de mapeamento de textura
				//CT = ID % TTC;
				//RT = ID / TTC;
				//fragment shader:
				//vt.x = CT * TTW;
				//vt.y = RT * TTH;

				//desenha triângulos para o tile

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