//Includes the SineWaveVertexGen.h header file

#include "SineWaveVertexGen.h"

//Defines the function sineCurveGeneration
std::vector<float> sineCurveGeneration()
{
	float function_domain = 360;
	std::vector<float> flat_coords;
	for (int i = -function_domain; i < function_domain; i++)
	{
		//Adds x coord to list and normalises it so that i can be used immediatly by opengl
		flat_coords.push_back(i/function_domain);				//X coord
		//Calculates Y coord of sine by turning the x value into radians using a custom efined PI value and then using the math sin function 
		flat_coords.push_back(sin((i*PI)/180));		//Y coord			
	}
	return flat_coords;
}

