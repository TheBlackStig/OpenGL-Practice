//Include ehader file
#include "mainWindow.h"

//main function to render window

int main()
{
	//Window dimensions
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	//Initialise opengl
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create window object
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SineWave", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Windoe creation failed!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	//Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 0;
}

//Input function
void processInput(GLFWwindow* window)
{

}

//Frame buffer call back function
void frameBufferSizeCallback(GLFWwindow* window, int height, int width)
{
	glViewport(0, 0, width, height);
}