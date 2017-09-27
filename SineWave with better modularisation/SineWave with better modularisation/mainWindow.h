#pragma once

//Rendering libraries
#include <glad\glad.h>
#include <GLFW\glfw3.h>

//standard libraries
#include <iostream>
#include <vector>

void processInput(GLFWwindow* window);
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);