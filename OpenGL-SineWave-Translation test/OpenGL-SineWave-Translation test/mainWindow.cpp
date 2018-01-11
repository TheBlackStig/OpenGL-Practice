#include "mainWindow.h"
#include "shaderObject.h"
#include "vertexGeneration.h"
const char *vert_shader_source = "#version 330 core\n"
"layout (location = 0) in vec 3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos,0.0);\n"
"}\0";
const char *frag_shader_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";	
int main()
{
	//glfw initialisation and setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create window and check if creation is successful
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SineWave Translation", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initalize glad" << std::endl;
		return -2;
	}
	//Call constructor for shader objects using filepaths fro shader source code
	Shader sine_wave_shader("C:\\Users\\SEvans\\Documents\\GitHub\\OpenGL-Practice\\OpenGL-SineWave-Translation test\\OpenGL-SineWave-Translation test\\vertex-shader.glvs",
		"C:\\Users\\SEvans\\Documents\\GitHub\\OpenGL-Practice\\OpenGL-SineWave-Translation test\\OpenGL-SineWave-Translation test\\fragment-shader.glfs");
	/*
	//Temp construction of shader
	unsigned int vert_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert_shader, 1, &vert_shader_source, NULL);
	glCompileShader(vert_shader);

	unsigned int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &frag_shader_source, NULL);
	glCompileShader(vert_shader);
	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, vert_shader);
	glAttachShader(shader_program, frag_shader);
	glLinkProgram(shader_program);*/
	//Load verticies
	//Verticies for sine wave
	std::vector<float> sine_wave_verticies = sineWaveGenerator(0.0,0.0,0.0);
	//std::vector<float> sine_wave_verticies = {-0.25f,0.1f,-1.0f, 0.25f,-0.1f,-1.0f};
	//VBOs and VAOs and EBOs
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sine_wave_verticies.size(), &sine_wave_verticies[0], GL_STATIC_DRAW);
	
	//Position attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glUseProgram(shader_program);
	sine_wave_shader.use();
	//Draw in wire mesh mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Render Loop
	while (!glfwWindowShouldClose(window))
	{
		//Take user inputs 
		processInput(window);

		//Render
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glUseProgram(shader_program);
		sine_wave_shader.use();
		/*//Draw	transformations
		glm::mat4 transform;
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		
		//Call the relevant shader to be used
		sine_wave_shader.use();
		//Tranformations on shader
		unsigned int transformLoc = glGetUniformLocation(sine_wave_shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		*/
		//Draw a sinewave
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_STRIP, 0, sine_wave_verticies.size());


		//Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

///DEBUGGING FUCNTIO NTO RETURN VALUES OF A VECTOR
void vectorDebug(std::vector<float> in_vector, int num_display)
{
	for (int i = 0; i < in_vector.size(); i++)
	{
		std::cout << in_vector[i] << ", ";
	}
	std::cout << std::endl;
}