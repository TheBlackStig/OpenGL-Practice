#pragma once

//Includes

#include <iostream>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

//transformation libraries
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

//Standard libaries
#include <vector>

///Debugging assert library
#include <assert.h>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void vectorDebug(std::vector<float> in_vector, int num_display);