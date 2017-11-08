#include "Window.h"

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

int main()
{
	//Initialise window and configure window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Window creating and check for creating window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Menu Practice", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Window creation failed." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);

	//Load and initialise glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load GLAD." << std::endl;
		return -2;
	}

	//The Render Loop
	while (!glfwWindowShouldClose(window))
	{
		//Inputs
		processInput(window);
		//Rendering
		glClearColor(0.2f, 0.3f, 0.4f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{

}

void processInput(GLFWwindow* window)
{

}