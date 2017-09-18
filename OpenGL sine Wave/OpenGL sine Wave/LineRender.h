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
		"version #330 core\n"
		"layout (location = 0) in vec3 pos;\n"
		"{\n"
		"	gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
public:
	void addVertices(std::vector<float> vertex_coords);
	void returnVertices();
	void VBOBufferCreation();
	void vertexShaderCompiler();
};
