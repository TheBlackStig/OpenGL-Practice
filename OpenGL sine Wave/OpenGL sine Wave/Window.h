#pragma once

#include <iostream>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

//Main fucntion where render loop is and all instatisation takes place
int main();

/*Set viewport size to screen width-100 and screen height-100 so that options 
can be displayed around the edge of the rendering window*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int vertexShaderCompiler(const char* shader_source);