#pragma once

//Includes the file containing functions for all sine wave operations
#include "SineWaveVertexGen.h"

//Includes GLAD
#include <glad/glad.h>
//Includes GLFW
#include <GLFW/glfw3.h>

//Input output library
#include <iostream>
//Main fucntion where render loop is and all instatisation takes place
int main();

/*Set viewport size to screen width-100 and screen height-100 so that options 
can be displayed around the edge of the rendering window*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//Processes the input and quits of ESC is pressed
void processInput(GLFWwindow *window);
//Compiler for the vertex shader
unsigned int vertexShaderCompiler(const char* shader_source);
//Compiler for the fragment shaders
unsigned int fragmentShaderCompiler(const char* shader_source);