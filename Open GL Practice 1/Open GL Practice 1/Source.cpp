///Just some fun with open gl

//Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


//The magic libary, include before gl.h and glfw.h.
#include<glad/glad.h>
#include <glfw/glfw3.h>

//Function declarations
//Auto frame adjust
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//Escape key closes window
void processInput(GLFWwindow* window);	
//Vertex shader compiler 
int vertexShaderCompiler(const char* source);
//Fragment shader compiler
int fragmentShaderCompiler(const char* source);
//Links two shader programs
int shaderProgramLinker(int vertex_shader, int fragment_shader);
//Screen settings
const unsigned int SCR_WIDTH = 800;	
const unsigned int SCR_HEIGHT = 600;

//Vertex shader source code
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
//Fragment shader source code
const char *fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";
int main()
{
	//GLFW initialise and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//GLFW window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Practice", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Viewport
	//Viewport auto adjust
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//GLAD Initialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//Build and compile the vertex shader program
	int vertex_shader_compiled= vertexShaderCompiler(vertexShaderSource);

	//Build and compile the fragment shader program
	int fragment_shader_compiled = fragmentShaderCompiler(fragmentShaderSource);

	//Link Shaders
	int shaderProgram = shaderProgramLinker(vertex_shader_compiled, fragment_shader_compiled);

	//Triangle
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	//Takes 4 coords from verticites and specifies which coords should be rendered and in which order
	unsigned int indices[] = {
		0,1,3,		//First triangle
		1,2,3
	};
	//0, copy verticies array in a buffer for OpenGLto use
	unsigned int VBO,VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//Bind VAO object first then set vertex buffers, the nconfigure vertex attributes
	glBindVertexArray(VAO);
	//Bind Element array buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Set vertex attriute pointers	 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Renderloop (keeps the window on the screen until an action)
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//Rendering commands
		glClearColor(0.2f, 0.25f, 0.3f, 0.3f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw in wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//Draw Triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//Clears all allocated resources
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int vertexShaderCompiler(const char* source)
{
	//Build and compile the vertex shader program
	int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &source, NULL);
	glCompileShader(vertex_shader);
	///Checks if the shader has been compiled correctly
	int success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return vertex_shader;
}

int fragmentShaderCompiler(const char* source)
{
	int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &source, NULL);
	glCompileShader(fragment_shader);
	///Chefckc for erros when compiling
	int success;
	char info_log[512];
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPLIATION_FAILED\n" << info_log << std::endl;
	}

	return fragment_shader;
}

int shaderProgramLinker(int vertex_shader, int fragment_shader)
{
	int shader_program;
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	///Checks for successful link
	int success;
	char info_log[512];
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}