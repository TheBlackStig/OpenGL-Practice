#include "Window.h"
#include "SineWaveVertexGen.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


//Window settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//Shader source code
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char *blue_frag_shader = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.423f, 0.964f, 0.352f, 1.0f);\n"
"}\0";

int main()
{
	//GLFW initialize and configure
	glfwInit();														//Inital intantiasation od object
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					//Version of GLFW major
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);					//Version of GLFW minor
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//Core profile version

	//GLFW window creation using constants SCR_WIDTH and SCR_HEIGHT
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	//Checks for successful window creation
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//Checks of OS has chanegd veiwport size on start
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Load all OpenGL function pointers with GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	//Build and compile shader program for sinewave
	//Vertex shader compilation
	unsigned int vertex_shader = vertexShaderCompiler(vertexShaderSource);
	//Fragment shader compilation
	unsigned int sine_fragment_shader = fragmentShaderCompiler(fragmentShaderSource);
	// link shaders
	int success;
	char info_log[512];
	int shader_program = glCreateProgram();
	//Attach the vertex shader to the sine wave shader program
	glAttachShader(shader_program, vertex_shader);
	//Attach the fragment shader for the sine wave shader program
	glAttachShader(shader_program, sine_fragment_shader);
	//Link the two shaders together to form a single shader
	glLinkProgram(shader_program);
	//Check for linking errors
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}
	//Vertex shader isnt deleted yet as it is used next
	glDeleteShader(sine_fragment_shader);

	//Build and compile shader program for axis
	//Note that the vertex shader from the previous is used as that can be identical
	unsigned int axis_fragment_shader = fragmentShaderCompiler(blue_frag_shader);
	int axis_shader_program = glCreateProgram();
	//Attach the vertex shader to the axis shader program
	glAttachShader(axis_shader_program, vertex_shader);
	//Attach the axis fragment shader to the axis shader program
	glAttachShader(axis_shader_program, axis_fragment_shader);
	//Link the two shaders together to form a single shader 
	glLinkProgram(axis_shader_program);
	//Check for linking errors
	glGetProgramiv(axis_shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(axis_shader_program, 512, NULL, info_log);
		std::cout << "ERROR::AXIS::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}

	//Set up vertex data (and buffer(s)) and configure vertex attributes
	//Sinewave
	std::vector<float> vertices = sineCurveGeneration();
	//Displays vector sine wave
	vectorDisplay(vertices);
	//Penguin attempt
	/*float vertices[] = {-0.04f,0.8f,
		0.04f,0.8f,
		0.08f,0.75f,	//Right side of face
		0.09f,0.7f,
		0.085f,0.65f,
		0.2f,0.5f,
		0.25f,0.45f,
		0.2f,0.4f,
		0.15f,0.4f,
		0.2f,0.3f,
		0.08f,0.1f,// Now acrros to right
		-0.08f,0.1f,
		-0.2f,0.3f,
		-0.15f,0.4f,
		-0.2f,0.4f,
		-0.25f,0.45f,
		-0.2f,0.5f,
		-0.085f,0.65f,
		-0.09f,0.7f,
		-0.08f,0.75f,
		-0.04f,0.8f


	};*/
	/*
	//Triangle
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		//-0.5f,  0.5f, 0.0f   // top left 
	};*/
	/*unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};*/
	//Axis coords
	float axis[] = { -1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, -1.0f };


	///Buffer setup
	unsigned int VBO[2], VAO[2];
	//Generate 2 Vertex Attribute Objects
	glGenVertexArrays(2, VAO);
	//Generate 2 Vertex Buffer Objects
	glGenBuffers(2, VBO);
	

	///For First set of VAO and VBO for sine wave
	glBindVertexArray(VAO[0]);														//Binding first VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);											//Binding first VBO
	glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices[0], GL_STATIC_DRAW);	//Binding vertex data to the buffer 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//Telling opengl how to interpret the data
																					//In this case it is in 3s x,y,z
	glEnableVertexAttribArray(0);													// enabling the buffer

	///For second set of VAO and VBO for axis
	glBindVertexArray(VAO[1]);														// Binding second VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);											// Binding second VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(axis), axis, GL_STATIC_DRAW);				//Binding vertex data to the buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);	//Telling opengl to interpret vertex as x,y
	glEnableVertexAttribArray(0);													//enabling the buffer

	//Allows any shapes to be drawn in a line mode 
	//As only lines are being drawn this isn't needed
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//The render loop
	while (!glfwWindowShouldClose(window))
	{
		//Check for inputs
		processInput(window);

		//Render the screen with background color of black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		///Draw sinewave
		//Set width of line
		glLineWidth(1);
		//Tell openGL which shader program to use
		glUseProgram(shader_program);
		//Binding the VAO to the sine wave 
		glBindVertexArray(VAO[0]);
		//Draw the sinewave with the given 3D coords
		glDrawArrays(GL_POINTS, 0, vertices.size());


		///Drawing axis
		//Set wdith of lines
		glLineWidth(2);
		//Tell openGL which shader program to use
		glUseProgram(axis_shader_program);
		//Binding VAO to axis array 
		glBindVertexArray(VAO[1]); 
		//Drawing axis
		glDrawArrays(GL_LINE_STRIP, 0, sizeof(axis));


		//Swap the buffers for the window ready for next frame render
		glfwSwapBuffers(window);
		//Poll the events (e.g. button clicks)
		glfwPollEvents();
	}

	//Deallocate all resources once they are finished with
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);

	//Terminate all glfw processes and data
	glfwTerminate();
	return 0;
}

//Process all inputs: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//Whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Make sure the viewport matches the new window dimensions; note that width and 
	//Height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

unsigned int vertexShaderCompiler(const char* shader_source)
{
	//Build and compile shader program
	//Vertex shader
	int vertex_shader_compiled = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_compiled, 1, &shader_source, NULL);
	glCompileShader(vertex_shader_compiled);
	//Check for shader compile errors
	int success;
	char info_log[512];
	glGetShaderiv(vertex_shader_compiled, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader_compiled, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	return vertex_shader_compiled;
}

unsigned int fragmentShaderCompiler(const char* shader_source)
{
	//Build and compile shader program
	//Fragment shader
	
	int fragment_shader_compiled = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_compiled, 1, &shader_source, NULL);
	glCompileShader(fragment_shader_compiled);
	// check for shader compile errors
	int success;
	char info_log[512];
	glGetShaderiv(fragment_shader_compiled, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader_compiled, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	return fragment_shader_compiled;
}