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

	//Initilisation of GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << " FAILED TO INITIALISE GLAD." << std::endl;
		return -1;
	}
	return 0;
}