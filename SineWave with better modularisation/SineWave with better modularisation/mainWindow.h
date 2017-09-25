#pragma once

//Rendering libraries
#include <GLFW\glfw3.h>
#include <glad\glad.h>
//standard stream libraries
#include <iostream>

void processInput(GLFWwindow* window);
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);