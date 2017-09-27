#include "Window.h"
#include "LineRender.h"
#include "SineWaveVertexGen.h"

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
	glfwMakeContextCurrent(window);

	//Call viewport resize check
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Initilisation of GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << " FAILED TO INITIALISE GLAD." << std::endl;
		return -2;
	}
	
	//Creates a sineline object and adds the vertex coords
	sineLine sine_wave_one;
	sine_wave_one.addVertices(sineCurveGeneration());
	std::vector<float> vertices = sine_wave_one.returnVertices();
	sine_wave_one.VBOBufferCreation();
	/*Compiles the vertex shader, fragment shader and then links the two
	in a shader program and then calls the shader program to be used.*/
	unsigned int shader_program = sine_wave_one.shaderProgramLinker(sine_wave_one.vertexShaderCompiler(), sine_wave_one.vertexShaderCompiler());
	//Set vertex attribute pointers
	//Generate a Vertex Array Object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//The render loop
	while (!glfwWindowShouldClose(window))
	{
		//Sets color of window
		glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES,0,sizeof(vertices)-1);

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