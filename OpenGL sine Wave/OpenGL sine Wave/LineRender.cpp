#include "LineRender.h"

void sineLine::addVertices(std::vector<float> vertex_coords)
{
	for (int i = 0; i < sizeof(vertex_coords); i++)
	{
		sineLine::vertices.push_back(vertex_coords[i]);
	}
}

void sineLine::returnVertices(std::vector<float> vertices)
{
	for (int i = 0; i < sizeof(vertices); i++)
	{
		std::cout << vertices[i] << std::endl;
	}
}