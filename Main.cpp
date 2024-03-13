#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{

	// Sets up the basics of GLFW and creates the window.

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(
		800, 600, // Window Size (width x height)
		"Hello Mum !", // Window Title
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
		processInput(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glViewport(
		0, 0, // Set the location of the lowest left pixel (or somethin)
		800, 600 // Sets the size of the viewport
	);

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

