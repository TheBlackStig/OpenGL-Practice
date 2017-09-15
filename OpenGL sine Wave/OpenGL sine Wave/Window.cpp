#include "Window.h"

int main()
{
	//Screen width and height 
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	const char WINDOW_NAME[] = "Sine Wave Render";

	//InstantiateGLFW window 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//	Construct window object
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME, NULL, NULL);
	//Check for window initilisation
	if (window == NULL)
	{
		std::cout << "FAILED TO CREATE WINDOW." << std::endl;
		glfwTerminate();
		return -1;
	}

	//Call viewport resize check
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Initilisation of GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << " FAILED TO INITIALISE GLAD." << std::endl;
		return -2;
	}


	//The render loop
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Terminates the window
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	/*Set viewport size to screen width-100 and screen height-100 so that options
	can be displayed around the edge of the rendering window*/
	glViewport(0, 0, width - 100, height - 100);
}