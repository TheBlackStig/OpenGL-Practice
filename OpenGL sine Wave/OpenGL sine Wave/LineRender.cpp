#include "LineRender.h"


//Adds the x,y coords to the vertex vector and convertes them to 3D
void sineLine::addVertices(std::vector<float> vertex_coords)
{
	for (int i = 0; i < sizeof(vertex_coords); i++)
	{
		if (i + 1 % 3 != 0) {
			sineLine::vertices_vector.push_back(vertex_coords[i]);
		}
		else {
			sineLine::vertices_vector.push_back(0.0f);
		}
	}
}
//Returns the contents of the vertex vector 
void sineLine::returnVertices()
{
	for (int i = 0; i < sizeof(sineLine::vertices_vector); i++)
	{
		std::cout << sineLine::vertices_vector[i] << std::endl;
	}
}

//Creates a vertex buffer object and binds it to the appropriate buffers

void sineLine::VBOBufferCreation()
{
	//Not sure why but it doesnt like the pointer to the class data member 
	//Going to cheat and make a new variable and point to that for now
	std::vector<float> temp_vector = sineLine::vertices_vector;
	unsigned int VBO;
	//Gnerates the vertex buffer object and binds it to the array buffer of the wave verticies
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sineLine::vertices_vector), &temp_vector, GL_STATIC_DRAW);
}

void sineLine::vertexShaderCompiler()
{
	//Not sure why but it doesnt like the pointer to the class data member 
	//Going to cheat and make a new variable and point to that for now
	const char *shader_source = sineLine::vertex_shader_source;
	//Compiles the vertex shader 
	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &shader_source, NULL);
	glCompileShader(vertex_shader);

	//Checks for successful compilation 
	int success;
	char info_log[512];
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cout << "Vertex shader compilation fail." << info_log << std::endl;
	}
}

void sineLine::fragmentShaderCompiler()
{
	const char *frag_shader_scource = sineLine::fragment_shader_source;
	unsigned int frag_shader;
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &frag_shader_scource, NULL);
	glCompileShader(frag_shader);

}
