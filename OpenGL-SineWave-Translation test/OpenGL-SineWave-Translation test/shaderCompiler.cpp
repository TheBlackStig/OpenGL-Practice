#include "shaderCompiler.h"

unsigned int vertexShaderCompiler(const char* vertex_shader_source)
{
	//Take shader source and compile the vertex shader
	unsigned int vertex_shader_compiled = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_compiled, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader_compiled);
	//Check for successful compilation
	int success;
	char info_log[512];
	glGetShaderiv(vertex_shader_compiled, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader_compiled, 512, NULL, info_log);
		std::cout << "Vertex shader compile failed. " << info_log << std::endl;
	}
	return vertex_shader_compiled;
}

unsigned int fragmentShaderCompiler(const char* fragment_shader_source)
{
	//Take shader source and compile the fragment shader
	unsigned int fragment_shader_compiled = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_compiled, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader_compiled);
	//Check for successful compilation
	int success;
	char info_log[512];
	glGetShaderiv(fragment_shader_compiled, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader_compiled, 512, NULL, info_log);
		std::cout << "Fragment shader compile failed." << info_log << std::endl;
	}

	return fragment_shader_compiled;
}

int shaderLinker(unsigned int vertex_shader, unsigned int fragment_shader)
{
	//Attach vertex and fragment shaders to final shader and link the two.
	int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	
	//Check for linking errors
	int success;
	char info_log[512];
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cout << "Shader linking failed." << info_log << std::endl;
	}
	return shader_program;
}