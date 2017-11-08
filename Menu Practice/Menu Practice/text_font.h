#pragma once
//Uses https://www.codeproject.com/Articles/30775/TetroGL-An-OpenGL-Game-Tutorial-in-C-for-Win32-pla
//Includes
#include <string>
#include <glad\glad.h>
#include <GLFW\glfw3.h>



//Creates a class for a custom font in C++ OpenGL GLFW
class text_font
{
public:
	//default constructor
	text_font();
	//default destructor
	~text_font();

	//Create a font with specific height and weight
	void createFont(const std::string& strTypeface,
		int iFontHeight,
		int iFontWeight);

	//Draw the text on the screen at the specified location with specified colour
	void drawText(const std::string& strText, 
		int xPos,
		int yPos,
		GLfloat fRed,
		GLfloat fGreen,
		GLfloat fBlue);

	static void setDeviceContext(HDC hDevContext)
};

