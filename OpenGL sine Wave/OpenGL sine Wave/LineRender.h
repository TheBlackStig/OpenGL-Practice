#pragma once

//Custom includes
#include "SineWaveVertexGen.h"

//Standard includes
#include <iostream>
#include <vector>

//OpenGL includes
#include <glad\glad.h>
#include <GLFW\glfw3.h>


//Class for creating an object to represent a sine wave
class sineLine 
{
private:
	std::vector<float> vertices_vector;
	const char *vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char *fragment_shader_source =
		"#version 330 core\n"
		"out vec4 frag_color;\n"
		"void main()\n"
		"{\n"
		"	frag_color = vec4(1.0f,0.5f,0.2f,1.0f);\n"
		"}\0";
public:
	void addVertices(std::vector<float> vertex_coords);
	std::vector<float> returnVertices();
	unsigned int VBOBufferCreation();
	unsigned int vertexShaderCompiler();
	unsigned int fragmentShaderCompiler();
	unsigned int shaderProgramLinker(unsigned int vertex_shader,unsigned int frag_shader);
};
