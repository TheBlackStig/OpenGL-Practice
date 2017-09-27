#include "LineRender.h"


//Adds the x,y coords to the vertex vector and convertes them to 3D
void sineLine::addVertices(std::vector<float> vertex_coords)
{
	for (int i = 0; i < sizeof(vertex_coords); i++)
	{
		if (i + 1 % 3 != 0) {
			sineLine::vertices_vector.push_back(vertex_coords[i]);
		}
		else {
			sineLine::vertices_vector.push_back(0.0f);
		}
	}
}
//Returns the contents of the vertex vector 
std::vector<float> sineLine::returnVertices()
{
	for (int i = 0; i < sizeof(sineLine::vertices_vector); i++)
	{
		std::cout << sineLine::vertices_vector[i] << std::endl;
	}
	return sineLine::vertices_vector;
}

//Creates a vertex buffer object and binds it to the appropriate buffers

unsigned int sineLine::VBOBufferCreation()
{
	//Not sure why but it doesnt like the pointer to the class data member 
	//Going to cheat and make a new variable and point to that for now
	std::vector<float> temp_vector = sineLine::vertices_vector;
	unsigned int VBO;
	//Gnerates the vertex buffer object and binds it to the array buffer of the wave verticies
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sineLine::vertices_vector), &temp_vector, GL_STATIC_DRAW);

	return VBO;
}

unsigned int sineLine::vertexShaderCompiler()
{
	/*Not sure why but it doesnt like the pointer to the class data member
	as it needs to have a pointer to the beggining of the vector
	Going to cheat and make a new variable and point to that for now*/
	const char *shader_source = sineLine::vertex_shader_source;
	//Creates the variable for the shader to be stored in
	unsigned int vertex_shader;
	//Creates a shader type 
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	//Tells the compiler wher to put the compield shader and where teh source is located
	glShaderSource(vertex_shader, 1, &shader_source, NULL);
	//Compiels the shader
	glCompileShader(vertex_shader);

	//Checks for successful compilation and returns and error message if it fails
	int success = NULL;
	char info_log[512];
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cout << "Vertex shader compilation fail." << info_log << std::endl;
		return 1;
	}
	return vertex_shader;
}

unsigned int sineLine::fragmentShaderCompiler()
{
	/*Not sure why but it doesnt like the pointer to the class data member 
	as it needs to have a pointer to the beggining of the vector
	Going to cheat and make a new variable and point to that for now*/
	const char *frag_shader_scource = sineLine::fragment_shader_source;
	//Variable to store the fragment shader
	unsigned int frag_shader;
	//Creates the fragment shader type
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	//Tells the compiler where to put the compiled shader and where to get the source from
	glShaderSource(frag_shader, 1, &frag_shader_scource, NULL);
	//Compiles the shader from the source
	glCompileShader(frag_shader);

	//Checks for successful compilation and returns an error message if it fails
	int success = NULL;
	char info_log[512];
	if (!success)
	{
		glGetShaderInfoLog(frag_shader, 512, NULL, info_log);
		std::cout << "Vertex shader compilation fail." << info_log << std::endl;
		return 1;
	}
	return frag_shader;
}

unsigned int sineLine::shaderProgramLinker(unsigned int vertex_shader, unsigned int frag_shader)
{
	//Creates variable to contain shader program
	unsigned int shader_program;
	//creates rhe shader program type
	shader_program = glCreateProgram();
	//Attaches the vertex shader to the shader program
	glAttachShader(shader_program, vertex_shader);
	//Attaches the fragment shader to the shader program
	glAttachShader(shader_program, frag_shader);
	//Links the two shaders into the single program
	glLinkProgram(shader_program);

	//Checks for successful link
	int success;
	char info_log[512];
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cout << "Shader program link failed: " << info_log << std::endl;
	}

	//Deletes the shaders so they are out of memory
	glDeleteShader(frag_shader);
	glDeleteShader(vertex_shader);

	//Returns the shader program
	return shader_program;
}