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
	Shader(const GLchar* vert_shader_path, const GLchar* frag_shader_path)
	{
		//Rertrieve the shaders from the shader file path
		//Strings for storing the shader code once read in
		std::string vert_shader_code;
		std::string frag_shader_code;
		//Setup of the file streams
		std::ifstream vert_shader_file;
		std::ifstream frag_shader_file;
		//Checks that any expetions can be thrown if needed 
		vert_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		frag_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		//Tries to open the files and throws an exception if it fails
		try
		{
			//Open the files for reading 
			vert_shader_file.open(vert_shader_path);
			frag_shader_file.open(frag_shader_path);
			//set uo the buffer streams before reading
			std::stringstream vert_shader_stream, frag_shader_stream;
			//Read the buffer contents into the streams
			vert_shader_stream << vert_shader_file.rdbuf();
			frag_shader_stream << frag_shader_file.rdbuf();
			//Close the files as all the data is now in the streams
			vert_shader_file.close();
			frag_shader_file.close();
			//Convert the streams into strings for use in compiling
			vert_shader_code = vert_shader_stream.str();
			frag_shader_code = frag_shader_stream.str();
		}
		//catch and exceptions
		catch (std::ifstream::failure e)
		{
			std::cout << "FAILED TO LOAD AND READ SHADER FILES" << std::endl;
		}
		//convert the strings into chars so that they can be understodo by the compilers
		const char* vert_shader_source = vert_shader_code.c_str();
		const char* frag_shader_source = vert_shader_code.c_str();

		//Compile the shaders 
		//Take shader source and compile the vertex shader
		unsigned int vert_shader_compiled = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vert_shader_compiled, 1, &vert_shader_source, NULL);
		glCompileShader(vert_shader_compiled);
		//Check for compile errors in vertex shader
		checkCompileErrors(vert_shader_compiled, "VERTEX");
		//Take shader source and compile the fragment shader
		unsigned int frag_shader_compiled = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag_shader_compiled, 1, &frag_shader_source, NULL);
		glCompileShader(frag_shader_compiled);
		//Check for compile errors in fragment shader
		checkCompileErrors(frag_shader_compiled, "FRAGEMENT");

		//Create the shader program by linking the two shaders
		ID = glCreateProgram();
		glAttachShader(ID, vert_shader_compiled);
		glAttachShader(ID, frag_shader_compiled);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		//Delete the fragment and vertex shaders
		glDeleteShader(vert_shader_compiled);
		glDeleteShader(frag_shader_compiled);
	}
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