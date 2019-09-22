#include "System.h"


#include "stb_image.h"

#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float TELA_X = 640.0f;
float TELA_Y = 480.0f;
float CENTRO_X = TELA_X / 2;
float CENTRO_Y = TELA_Y / 2;

int sprite_direction = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
{
	sprite_direction = 2;
	if (key == GLFW_KEY_LEFT)
	{
		if (action == GLFW_REPEAT)
		{
			sprite_direction = 0;
		}
		else if (action == GLFW_PRESS) {
			sprite_direction = 1;
		}
		else {
			sprite_direction = 2;
		}
	}
	else if (key == GLFW_KEY_RIGHT)
	{
		if (action == GLFW_REPEAT)
		{
			sprite_direction = 4;
		}
		else if (action == GLFW_PRESS)
		{
			sprite_direction = 3;
		}
		else {
			sprite_direction = 2;
		}
	}
	else if (key == GLFW_KEY_SPACE)
	{
		//ally_shoot = 1;
	}
}


int main() {
	

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}
	/* Caso necess�rio, defini��es espec�ficas para SOs, p. e. Apple OSX *
	/* Definir como 3.2 para Apple OS X */
	/*glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
	GLFWwindow *g_window = glfwCreateWindow(
		640, 480, "Teste de vers�o OpenGL", NULL, NULL);
	if (!g_window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(g_window);
	// inicia manipulador da extens�o GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	

	/*float vertices[] = {
		// positions          // colors           // texture coords
		640.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		640.0f, 480.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		0.0f, 480.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
	};*/

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

	float vertices4[] = {
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

	// position attribute		                //de quanto em quanto	//onde come�a
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

	// position attribute		                //de quanto em quanto	//onde come�a
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

	// position attribute		                //de quanto em quanto	//onde come�a
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

	// position attribute		                //de quanto em quanto	//onde come�a
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

	// position attribute		                //de quanto em quanto	//onde come�a
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Shader ourShader("4.1.texture.vs", "4.1.texture.fs");
	
	float matrix[] = {
		1.0f, 0.0f, 0.0f, 0.0f, // 1� coluna
		0.0f, 1.0f, 0.0f, 0.0f, // 2� coluna
		0.0f, 0.0f, 1.0f, 0.0f, // 3� coluna
		0.25f, 0.25f, 0.0f, 1.0f // 4� coluna
	};

	//glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

	/*const char* vertex_shader =
		"#version 410 core\n"
		"layout(location = 0) in vec3 aPos;"
		"layout(location = 1) in vec3 aColor;"
		"layout(location = 2) in vec2 aTexCoord;"

		"out vec3 ourColor;"
		"out vec2 TexCoord;"

		"uniform mat4 proj; "
		

		"void main(){"
			"gl_Position = proj * vec4(aPos, 1.0);"
			"ourColor = aColor;"
			"TexCoord = vec2(aTexCoord.x, aTexCoord.y);"
		"}";

	const char* fragment_shader =
		"#version 410 core\n"
		"out vec4 FragColor;"

		"in vec3 ourColor;"
		"in vec2 TexCoord;"

		// texture sampler
		"uniform sampler2D texture1;"
		"uniform sampler2D texture2;"

		"void main(){"
			"FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);"
			"if (FragColor.a < 0.5) discard;"
		"}";
	*/

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
		"gl_Position = proj * vec4(vertex_position, layer_z, tamanho);"
		"}";

	const char* fragment_shader =
		"#version 410\n"
		"in vec2 texture_coords;"
		"uniform sampler2D sprite;"
		"uniform float offsetx;"
		"uniform float offsety;"
		
		"out vec4 frag_color;"
		"void main () {"
		"vec4 texel = texture (sprite, vec2(texture_coords.x + offsetx, texture_coords.y + offsety));"
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


	unsigned int texture1, texture2, texture3, texture4, texture5;
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


	glUseProgram(shader_programme);
	glUniform1i(glGetUniformLocation(shader_programme, "texture1"), 0);

	//int matrixLocation = glGetUniformLocation(shader_programme, "matrix");
	//glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);
	
	glm::mat4 proj = glm::ortho(0.0f, TELA_X, TELA_Y, 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(
		glGetUniformLocation(shader_programme, "proj"), 1,
		GL_FALSE, glm::value_ptr(proj));

	

	float speed = 1.0f;
	float lastPosition = 0.0f;

	float layers[5];
	layers[0] = texture1;
	layers[1] = texture2;
	layers[2] = texture3;
	layers[3] = texture4;
	layers[4] = texture5;

	float layersZ[5];
	layersZ[0] = -1.0;
	layersZ[1] = -1.0;
	layersZ[2] = -0.9;
	layersZ[3] = -0.8;
	layersZ[4] = -0.7;

	float vao[5];
	vao[0] = VAO;
	vao[1] = VAO2;
	vao[2] = VAO3;
	vao[3] = VAO4;
	vao[4] = VAO5;


	float movimentoCeu = 0.5;
	float movimentoCarro = 0.5;
	while (!glfwWindowShouldClose(g_window))
	{
		processInput(g_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
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
		
		for (int i = 0; i < 5; i++) {

			glBindVertexArray(vao[i]);

			if (i == 0) {

				movimentoCeu += 0.15 * 0.0009f;
				glUniform1f(
					glGetUniformLocation(shader_programme, "offsetx"), movimentoCeu);

			} else if (i == 4) {
			
				movimentoCarro += 0.7 * 0.0009f;
				glUniform1f(
					glGetUniformLocation(shader_programme, "offsetx"), movimentoCarro);

			} else {
			
				glUniform1f(
					glGetUniformLocation(shader_programme, "offsetx"), 1);

			}

			glUniform1f(
				glGetUniformLocation(shader_programme, "offsety"), 1);
			glUniform1f(
				glGetUniformLocation(shader_programme, "layer_z"), layersZ[i]);
			glUniform1f(
				glGetUniformLocation(shader_programme, "tamanho"), 1);
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