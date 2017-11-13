#pragma once

//Includes

#include <iostream>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);