#pragma once

#include <iostream>

#include <glad\glad.h>

#include <GLFW\glfw3.h>

//Function identifiers for shader compilers one for vertex and one for fragment

//Vertex shader compiler
unsigned int vertexShaderCompiler(const char* vertex_shader_source);
//Fragment shader compiler
unsigned int fragmentShaderCompiler(const char* fragment_shader_source);
//Shader linker
int shaderLinker(unsigned int vertex_shader, unsigned int fragment_shader);