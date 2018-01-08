//Include Guard
#ifndef SHADER_H
#define SHADER_H


//Includes
//Standard input output stream library
#include <iostream>
//String library
#include <string>
//Gl loader
#include <glad\glad.h>
//File stream libraries
#include <fstream>
#include <sstream>

//Class tempalte for a shader object
//All the functions are defined in a single file as this allows for potability to other projects or versions
class Shader
{
public:
	//Program ID for the shader
	unsigned int ID;

	//Constructor reads the shader programs then compiles them as and when they are needed 
	Shader(const GLchar* vert_shader_path, const GLchar* frag_shader_path);

	//Use the shader or activate the shader
	void use()
	{
		glUseProgram(ID);
	}

	//Uniform utility functions
	void setBool(const std::string &name, bool value)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setInt(const std::string &name, bool value)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string &name, bool value)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

private:
	//Internal fucntion for checking for compile/linking errors within the constructor
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char info_log[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, info_log);
				std::cout << "ERROR IN " << type << " SHADER COMPILATION" << "\n" << info_log << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, info_log);
				std::cout << "ERROR IN PROGRAM LINKING OF TYPE: " << type << "\n" << info_log << std::endl;
			}
		}
	}
};

#endif