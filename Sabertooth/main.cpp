#include "System.h"

#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


glm::mat4 matrix_origem = glm::mat4(1);
glm::mat4 matrix_pessoa = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
glm::mat4 matrix_carro = glm::translate(glm::mat4(1), glm::vec3(0,0,0));

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
		fprintf(stderr, "ERROR: could not start GLFW3\n");
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
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
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

	float vertices1[] = {
		// positions          // colors           // texture coords
		0.0f, 480.0f, 0.0f,   1.0f, 1.0f, // buttom right
		0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top left
		640.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
		640.0f, 480.0f, 0.0f,   0.0f, 1.0f //top right
	};

	float vertices2[] = {
		// positions          // colors           // texture coords
		0.0f, 480.0f, 0.0f,   1.0f, 1.0f, // buttom right
		0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top left
		640.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
		640.0f, 480.0f, 0.0f,   0.0f, 1.0f //top right
	};

	float vertices3[] = {
		// positions          // colors           // texture coords
		0.0f, 480.0f, 0.0f,   1.0f, 1.0f, // buttom right
		0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top left
		640.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
		640.0f, 480.0f, 0.0f,   0.0f, 1.0f //top right
	};

	/*float vertices4[] = {
		// positions          // colors           // texture coords
		0.0f, 480.0f, 0.0f,   1.0f, 1.0f, // buttom right
		0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top left
		640.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
		640.0f, 480.0f, 0.0f,   0.0f, 1.0f //top right
	};*/

	float vertices4[] = {
		// positions          // colors           // texture coords
		0.0f, 480.0f, 0.0f,   1.0f, 1.0f, // buttom left
		0.0f, 350.0f, 0.0f,   1.0f, 0.0f, // top left
		300.0f, 350.0f, 0.0f,   0.0f, 0.0f, // top right
		300.0f, 480.0f, 0.0f,   0.0f, 1.0f //buttom right
	};

	float vertices5[] = {
		// positions          // colors           // texture coords
		0.0f, 480.0f, 0.0f,   1.0f, 1.0f, // buttom left
		0.0f, 350.0f, 0.0f,   1.0f, 0.0f, // top left
		300.0f, 350.0f, 0.0f,   0.0f, 0.0f, // top right
		300.0f, 480.0f, 0.0f,   0.0f, 1.0f //buttom right
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

	unsigned int VBO3, VAO3, EBO3;
	glGenBuffers(1, &EBO3);
	glGenVertexArrays(1, &VAO3);
	glBindVertexArray(VAO3);

	glGenBuffers(1, &VBO3);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute		                //de quanto em quanto	//onde começa
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	unsigned int EBO4;
	glGenBuffers(1, &EBO4);

	unsigned int VBO4, VAO4;
	glGenVertexArrays(1, &VAO4);
	glBindVertexArray(VAO4);

	glGenBuffers(1, &VBO4);
	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute		                //de quanto em quanto	//onde começa
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int EBO5;
	glGenBuffers(1, &EBO5);

	unsigned int VBO5, VAO5;
	glGenVertexArrays(1, &VAO5);
	glBindVertexArray(VAO5);

	glGenBuffers(1, &VBO5);
	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute		                //de quanto em quanto	//onde começa
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	
	
	unsigned int EBO6;
	glGenBuffers(1, &EBO6);

	unsigned int VBO6, VAO6;
	glGenVertexArrays(1, &VAO6);
	glBindVertexArray(VAO6);

	glGenBuffers(1, &VBO6);
	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices5), vertices5, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
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
		"vec4 texel = texture (sprite, vec2((texture_coords.x + offsetx)*imagem, texture_coords.y + offsety));"
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


	unsigned int texture1, texture2, texture3, texture4, texture5, texture6;
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
	unsigned char *data = stbi_load("bin/Images/ceu.jpg", &width, &height, &nrChannels, SOIL_LOAD_RGBA);
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

	// texture 2
	// ---------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps

	data = stbi_load("bin/Images/casas-edit.png", &width, &height, &nrChannels, SOIL_LOAD_RGBA);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	// texture 3
	// ---------
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps

	data = stbi_load("bin/Images/calcada-edit.png", &width, &height, &nrChannels, SOIL_LOAD_RGBA);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	// texture 4
	// ---------
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	
	data = stbi_load("bin/Images/rua-edit.png", &width, &height, &nrChannels, SOIL_LOAD_RGBA);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps

	data = stbi_load("bin/Images/carro.png", &width, &height, &nrChannels, SOIL_LOAD_RGBA);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);


	glGenTextures(1, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps

	data = stbi_load("bin/Images/bonecos.png", &width, &height, &nrChannels, SOIL_LOAD_RGBA);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
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

	matrix_carro = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0.0f));
	matrix_pessoa = glm::translate(glm::mat4(1), glm::vec3(50, 130, 0.0f));
	

	float speed = 1.0f;
	float lastPosition = 0.0f;

	float layers[6];
	layers[0] = texture1;
	layers[1] = texture2;
	layers[2] = texture3;
	layers[3] = texture4;
	layers[4] = texture5;
	layers[5] = texture6;

	float layersZ[6];
	layersZ[0] = -0.50;
	layersZ[1] = -0.49;
	layersZ[2] = -0.48;
	layersZ[3] = -0.47;
	layersZ[4] = -0.45;
	layersZ[5] = -0.46;

	float vao[6];
	vao[0] = VAO;
	vao[1] = VAO2;
	vao[2] = VAO3;
	vao[3] = VAO4;
	vao[4] = VAO5;
	vao[5] = VAO6;


	float movimentoCeu = 0.1;
	float tamanhoPersonagem = 3.0;
	while (!glfwWindowShouldClose(g_window))
	{
		processInput(g_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		/*static double previousSeconds = glfwGetTime();
		double currentSeconds = glfwGetTime();
		double elapsedSeconds =
			currentSeconds - previousSeconds;
		previousSeconds = currentSeconds;
		if (fabs(lastPosition) > 1.5f) {
			matrix[12] = -1.5;
			lastPosition = matrix[12];
		}
		else {
			matrix[12] = elapsedSeconds * speed +
				lastPosition;
			lastPosition = matrix[12];
		}
		glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);*/
		
		glUseProgram(shader_programme);
		for (int i = 0; i < 6; i++) {

			glBindVertexArray(vao[i]);

			if (i == 0) {
				glUniform1f(
					glGetUniformLocation(shader_programme, "imagem"), 1);
				glUniform1f(
					glGetUniformLocation(shader_programme, "tamanho"), 1);
				movimentoCeu += 0.15 * 0.0001f;
				glUniform1f(
					glGetUniformLocation(shader_programme, "offsetx"), movimentoCeu);
				glUniformMatrix4fv(
					glGetUniformLocation(shader_programme, "matrix"), 1,
					GL_FALSE, glm::value_ptr(glm::mat4(1)));
			
			} else if (i == 4) {
				if (matrix_carro[3].x <= 650) {
					matrix_carro = glm::translate(matrix_carro, glm::vec3(0.4, 0, 0.0f));
				}
				else {
					matrix_carro[3].x = -400;
				}
				glUniformMatrix4fv(
					glGetUniformLocation(shader_programme, "matrix"), 1,
					GL_FALSE, glm::value_ptr(matrix_carro));
			
			} else if (i == 5) {
				

				glUniform1f(
					glGetUniformLocation(shader_programme, "tamanho"), tamanhoPersonagem);
				glUniform1f(
					glGetUniformLocation(shader_programme, "imagem"), 0.125);

				int stateD = glfwGetKey(g_window, GLFW_KEY_D);
				int stateW = glfwGetKey(g_window, GLFW_KEY_W);
				int stateA = glfwGetKey(g_window, GLFW_KEY_A);
				int stateS = glfwGetKey(g_window, GLFW_KEY_S);
				
				
				if (stateD == GLFW_PRESS)
				{
					if (matrix_pessoa[3].x <= 525) {
						matrix_pessoa = glm::translate(matrix_pessoa, glm::vec3(0.3, 0, 0.0f));
					}
				}
				if (stateW == GLFW_PRESS)
				{
					if (matrix_pessoa[3].y >= 120) {
						matrix_pessoa = glm::translate(matrix_pessoa, glm::vec3(0, -0.3, 0.0f));
						tamanhoPersonagem += 0.003;
						glUniform1f(
							glGetUniformLocation(shader_programme, "tamanho"), tamanhoPersonagem);
					}

				}
				if (stateA == GLFW_PRESS)
				{
					if (matrix_pessoa[3].x >= 0) {
						matrix_pessoa = glm::translate(matrix_pessoa, glm::vec3(-0.3, 0, 0.0f));
					}
				}
				if (stateS == GLFW_PRESS)
				{
					if (matrix_pessoa[3].y <=205) {
						matrix_pessoa = glm::translate(matrix_pessoa, glm::vec3(0, 0.3, 0.0f));
						tamanhoPersonagem += -0.003;
						glUniform1f(
							glGetUniformLocation(shader_programme, "tamanho"), tamanhoPersonagem);
					}
				}
				
				glUniformMatrix4fv(
					glGetUniformLocation(shader_programme, "matrix"), 1,
					GL_FALSE, glm::value_ptr(matrix_pessoa));

				
				
			
			}
			
			
			
			else {
				
				
				glUniform1f(
					glGetUniformLocation(shader_programme, "offsetx"), 1);

				glUniformMatrix4fv(
					glGetUniformLocation(shader_programme, "matrix"), 1,
					GL_FALSE, glm::value_ptr(glm::mat4(1)));
			}

			
			glUniform1f(
				glGetUniformLocation(shader_programme, "offsety"), 1);
			glUniform1f(
				glGetUniformLocation(shader_programme, "layer_z"), layersZ[i]);
		
			

			glBindTexture(GL_TEXTURE_2D, layers[i]);
			glUniform1i(glGetUniformLocation(shader_programme, "sprite"), 0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		}

		glfwSwapBuffers(g_window);
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO2);

	glDeleteVertexArrays(1, &VAO3);
	glDeleteBuffers(1, &VBO3);
	glDeleteBuffers(1, &EBO3);

	glDeleteVertexArrays(1, &VAO4);
	glDeleteBuffers(1, &VBO4);
	glDeleteBuffers(1, &EBO4);

	glDeleteVertexArrays(1, &VAO5);
	glDeleteBuffers(1, &VBO5);
	glDeleteBuffers(1, &EBO5);

	// encerra contexto GL e outros recursos da GLFW
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