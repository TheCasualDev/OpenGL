#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// window config
const unsigned int WIND_WIDTH = 800;
const unsigned int WIND_HEIGHT = 600;

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

	// render loop

	while (!glfwWindowShouldClose(window))
	{

		// input
		processInput(window);

		glClearColor(0.5f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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

