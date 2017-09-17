#pragma once


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
	std::vector<float> vertices;
public:
	void addVertices(std::vector<float> vertex_coords);
	void returnVertices(std::vector<float> vertices);

};
