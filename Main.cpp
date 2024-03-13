#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// window config
const unsigned int WIND_WIDTH = 600;
const unsigned int WIND_HEIGHT = 600;

// shader data

const char *vertexShaderSource = 
"#version 400 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
"}\0";

const char *fragmentShaderSource = 
"#version 400 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.9686f, 0.5f, 0.5098f, 0.1373f);"
"}\0";

int main()
{

	// Sets up the basics of GLFW and creates the window.

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(
		WIND_WIDTH, WIND_HEIGHT, // Window Size (width x height)
		"Hello Mum & Dad!", // Window Title
		NULL,
		NULL
	);

	if (window == NULL) // Checks to see if glfw creates a window, and if not cancels the process
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // Checks that GLAD is working I hope.
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	unsigned int vertexShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);            // Pass the kind of shader we wish to create
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Sets the source of the shader to the defined above shader code
	glCompileShader(vertexShader);								// Complies the shader

	// vertexShaderCompiler Checker / debugger

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); 
	glCompileShader(fragmentShader);

	// fragmentShaderCompiler Checker / debugger

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// shader program 

	unsigned int shaderProgram;

	shaderProgram = glCreateProgram();			   // creates a shader program
	glAttachShader(shaderProgram, vertexShader);   // attatches the vertex shader to the shader program
	glAttachShader(shaderProgram, fragmentShader); // attatches the fragment shader to the shader program
	glLinkProgram(shaderProgram);                  // links the two shaders together 

	// linking Checker / debugger

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKING::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// clean up the shader data
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// triangle data ??
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	// setup the vertex data

	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO); // Vertex Array Object
	glGenBuffers(1, &VBO); // Vertex Buffer Object

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // used to bind a buffer obejct to a buffer type 
	glBufferData(		   // Copies the defined buffer iinto buffer memory.
		GL_ARRAY_BUFFER,   // The type of buffer
		sizeof(vertices),  // The size of the data
		vertices,		   // The data we wish to send
		GL_STATIC_DRAW	   // How we wish for the GPU to handle the data, STATIC_DRAW means that we set it once but use it multiple times
	);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // read it on learnopengl.com I aint typing all that out
	glEnableVertexAttribArray(0); // 

	// render loop

	while (!glfwWindowShouldClose(window))
	{

		// input
		processInput(window);

		glClearColor(0.3608f, 0.1373f, 0.9686f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram); // use the shaders linked above
		glBindVertexArray(VAO); // sets the vertex array (still dunno what his means in human terms)
		glDrawArrays(GL_TRIANGLES, 0, 3); // render a primitive triangle using the built in Draw Array function :D

		// check and call events 
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow* window) // gets the key input
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) // Updates the windows viewport to scale with the window
{ 
	glViewport(0, 0, width, height);
}

