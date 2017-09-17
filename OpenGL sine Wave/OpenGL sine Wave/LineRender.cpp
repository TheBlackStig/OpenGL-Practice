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
//retursnthe contents of the vertex vector 
void sineLine::returnVertices()
{
	for (int i = 0; i < sizeof(sineLine::vertices_vector); i++)
	{
		std::cout << sineLine::vertices_vector[i] << std::endl;
	}
}

//Creates a vertex buffer object and binds it to the appropriate buffers
void VBOBufferCreation()
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sineLine::vertices_vector), sineLine::&vertices_vector, GL_STATIC_DRAW);
}