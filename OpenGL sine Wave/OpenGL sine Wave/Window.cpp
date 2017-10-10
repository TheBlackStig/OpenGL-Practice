#include "Window.h"

//Window settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//Shader source codes 
//Vertex shader scour code
const char *vertex_shader_source = "#version 330 core\n"	//Version declaration in thiscase 330 as we're using OpenGl 3.3
"layout (location = 0) in vec3 aPos;\n"						//Declare vertex input attributes of a type vec 3 for 3D coords with a name of aPos
"void main()\n"												//Define main function
"{\n"														
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"		//The output of the shader is always 4 coords but as we only need 3 the
"}\0";														// 'w' component can be set to 1 and x,y,z as aPos values
//Fragment shader for orange
const char *fragment_shader_source = "#version 330 core\n"	//Version declaration in this case 330 as we're using OpenGl 3.3
"out vec4 frag_color;\n"									//Declare the output values as a vec4 of name frag_color
"void main()\n"												//Define main fucntion of program
"{\n"
"   frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"			//Now assign frag_color to color orange using 4 normalised rgba values
"}\0";														// red, green, blue, alpha (opacity)
//Fragment shader for green
const char *green_frag_shader = "#version 330 core\n"		//Version declaration in this case 330 as we're using OpenGl 3.3
"out vec4 frag_color;\n"									//Define main function of program
"void main()\n"
"{\n"
"	frag_color = vec4(0.423f, 0.964f, 0.352f, 1.0f);\n"		//Now assign frag_color to color green using 4 normalised rgba values
"}\0";														// red, green, blue, alpha (opacity)

int main()
{
	//GLFW initialize and configure
	glfwInit();														//Inital intantiasation of glfw
	//Version of GLFW major first argument is what we want to configrue second is the version number
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Version of GLFW minor first argument is what we want to configrue second is the version number
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//Core profile version 

	//GLFW window creation using constants SCR_WIDTH and SCR_HEIGHT
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	//Checks for successful window creation
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Makes the context of the specified window current on the running thread
	glfwMakeContextCurrent(window);
	//Checks if OS has chanegd viewport size on start using the framebuffer_size_callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Load all OpenGL function pointers with GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	//Build and compile shader program for sinewave
	//Vertex shader compilation
	unsigned int vertex_shader = vertexShaderCompiler(vertex_shader_source);
	//Fragment shader compilation
	unsigned int sine_fragment_shader = fragmentShaderCompiler(fragment_shader_source);
	// link shaders
	int success;
	char info_log[512];
	int shader_program = glCreateProgram();
	//Attach the vertex shader to the sine wave shader program
	glAttachShader(shader_program, vertex_shader);
	//Attach the fragment shader for the sine wave shader program
	glAttachShader(shader_program, sine_fragment_shader);
	//Link the two shaders together to form a single shader
	glLinkProgram(shader_program);
	//Check for linking errors
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}
	//Vertex shader isnt deleted yet as it is used next
	glDeleteShader(sine_fragment_shader);

	//Build and compile shader program for axis
	//Note that the vertex shader from the previous is used as that can be identical
	unsigned int axis_fragment_shader = fragmentShaderCompiler(green_frag_shader);
	int axis_shader_program = glCreateProgram();
	//Attach the vertex shader to the axis shader program
	glAttachShader(axis_shader_program, vertex_shader);
	//Attach the axis fragment shader to the axis shader program
	glAttachShader(axis_shader_program, axis_fragment_shader);
	//Link the two shaders together to form a single shader 
	glLinkProgram(axis_shader_program);
	//Check for linking errors
	glGetProgramiv(axis_shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(axis_shader_program, 512, NULL, info_log);
		std::cout << "ERROR::AXIS::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}

	//Set up vertex data (and buffer(s)) and configure vertex attributes
	//Sinewave
	std::vector<float> vertices = sineCurveGeneration();
	//Displays vector sine wave
	//vectorDisplay(vertices);

	//Axis coordinates
	float axis[] = { -1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, -1.0f };


	///Buffer setup
	unsigned int VBO[2], VAO[2];
	//Generate 2 Vertex Attribute Objects
	glGenVertexArrays(2, VAO);
	//Generate 2 Vertex Buffer Objects
	glGenBuffers(2, VBO);
	

	///For First set of VAO and VBO for sine wave
	//Binding first VAO making it the active object which all subsequent functions will reference
	glBindVertexArray(VAO[0]);								
	//Binding first VBO to active VAO arguments - type of buffer, buffer pointer
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);	
	//Binding vertex data to the buffer arguments - target buffer object, size of buffer objects new data in bytes, 
	//a pointer to first value of the data, expected usage pattern static in this case as no animation is taking place.
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
	//Telling opengl how to interpret the data In this case it is in 3s x,y,z
	//Arguments - vertex attribute (0 from vertex shader), size of vertex attribute (vec3 so 3), specifies type of data, 
	//data normalised or not, specifies the stride bewteen set of coordiantes in bytes (3 * the size of float in bytes as usign 3D coordinates)
	//offset of data position in buffer and is cast as 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Enabling the buffer																				
	glEnableVertexAttribArray(0);													

	///For second set of VAO and VBO for axis
	//Binding second VAO making it the active object which all subsequent functions will reference
	glBindVertexArray(VAO[1]);	
	//Binding second VBO to active VAO arguments - type of buffer, buffer pointer
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);											
	//Binding vertex data to the buffer arguments - target buffer object, size of buffer objects new data in bytes, 
	//a pointer to first value of the data, expected usage pattern static in this case as no animation is taking place.
	glBufferData(GL_ARRAY_BUFFER, sizeof(axis), axis, GL_STATIC_DRAW);
	//Telling opengl to interpret vertex as pairs (x,y)
	//Arguments - vertex attribute (0 from vertex shader), size of vertex attribute (vec3 so 3), specifies type of data, 
	//data normalised or not, specifies the stride bewteen set of coordiantes in bytes (3 * the size of float in bytes as usign 3D coordinates)
	//offset of data position in buffer and is cast as 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	//Telling opengl to interpret vertex as x,y
	glEnableVertexAttribArray(0);													

	//The render loop
	while (!glfwWindowShouldClose(window))
	{
		//Check for inputs
		processInput(window);

		//Render the screen with background color of black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		///Draw sinewave
		//Set width of line
		glLineWidth(1);
		//Tell openGL which shader program to use
		glUseProgram(shader_program);
		//Binding the VAO to the sine wave 
		glBindVertexArray(VAO[0]);
		//Draw the sinewave with the given 3D coords
		glDrawArrays(GL_LINE_STRIP, 0, vertices.size());


		///Drawing axis
		//Set wdith of lines
		glLineWidth(2);
		//Tell openGL which shader program to use
		glUseProgram(axis_shader_program);
		//Binding VAO to axis array 
		glBindVertexArray(VAO[1]); 
		//Drawing axis
		glDrawArrays(GL_LINE_STRIP, 0, sizeof(axis));


		//Swap the buffers for the window ready for next frame render
		glfwSwapBuffers(window);
		//Poll the events (e.g. button clicks)
		glfwPollEvents();
	}

	//Deallocate all resources once they are finished with
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);

	//Terminate all glfw processes and data
	glfwTerminate();
	return 0;
}

//Process all inputs: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//Whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Make sure the viewport matches the new window dimensions; note that width and 
	//Height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

unsigned int vertexShaderCompiler(const char* shader_source)
{
	//Build and compile shader program
	//Vertex shader
	//Creates the initial shader object with the type of shader it is in this case a vertex shader
	int vertex_shader_compiled = glCreateShader(GL_VERTEX_SHADER);
	//Points the shader source code to the shader object taking the shader object, number of strings, the source code
	//The fine argument is the length of string by this can be calculated by the function
	glShaderSource(vertex_shader_compiled, 1, &shader_source, NULL);
	//Compiles the shader with the previously given attributes
	glCompileShader(vertex_shader_compiled);
	//Check for shader compile errors
	int success;
	char info_log[512];
	glGetShaderiv(vertex_shader_compiled, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader_compiled, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	return vertex_shader_compiled;
}

unsigned int fragmentShaderCompiler(const char* shader_source)
{
	//Build and compile shader program
	//Fragment shader
	//Creates the initial shader object with the type of shader it is in this case a fragment shader
	int fragment_shader_compiled = glCreateShader(GL_FRAGMENT_SHADER);
	//Points the shader source code to the shader object taking the shader object, number of strings, the source code
	//The fine argument is the length of string by this can be calculated by the function
	glShaderSource(fragment_shader_compiled, 1, &shader_source, NULL);
	//Compiles the shader with the previously given attributes
	glCompileShader(fragment_shader_compiled);
	//Check for shader compile errors
	int success;
	char info_log[512];
	glGetShaderiv(fragment_shader_compiled, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader_compiled, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	return fragment_shader_compiled;
}