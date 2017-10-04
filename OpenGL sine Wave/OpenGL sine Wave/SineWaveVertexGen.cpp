//Includes the SineWaveVertexGen.h header file

#include "SineWaveVertexGen.h"

//Defines the function sineCurveGeneration
std::vector<float> sineCurveGeneration()
{
	float function_domain = 360.0f;
	std::vector<float> flat_coords;
	for (float i = -function_domain; i < function_domain; i++)
	{
		//Adds x coord to list and normalises it so that i can be used immediatly by opengl
		flat_coords.push_back(float(i / function_domain));				//X coord
		//Calculates Y coord of sine by turning the x value into radians using a custom efined PI value and then using the math sin function 
		flat_coords.push_back(float(sin((i*PI) / 180.0f)));		//Y coord		
		flat_coords.push_back(0.0f);				//Z cooord set to 0 as we want 2D
	}
	return flat_coords;
}

void vectorDisplay(std::vector<float> input_vector)
{
	//Outputs headers
	std::cout << std::setw(8) << "x coords:" << std::setw(8) << "y coords" << std::endl;
	//Outputs the contents of the vector assuming it is as sets of 3 corods (x,y,z)
	for (int i = 0; i < input_vector.size()-1; i+=36)
	{
		std::cout << "X:" << input_vector[i] << std::setw(5) << "Y:" << input_vector[i + 1] <<
			std::setw(5) << "Z:" << input_vector[i + 2] << std::endl;
	}
}
