#include "LineRender.h"

void sineLine::addVertices(std::vector<float> verticies)
{
	
}

void sineLine::returnVertices(std::vector<float> vertices)
{
	for (int i = 0; i < sizeof(vertices); i++)
	{
		std::cout << vertices[i] << std::endl;
	}
}