//Includes the SineWaveVertexGen.h header file

#include "SineWaveVertexGen.h"

//Defines the function sineCurveGeneration
std::vector<float> sineCurveGeneration()
{
	//Range of x coords in degrees
	float function_domain = 360.0f;
	//vector of floats to store the values
	std::vector<float> flat_coords;
	//Iterating through the range of -function_domain to function_domain in steps of 1 
	for (float i = -function_domain; i < function_domain; i++)
	{
		//Adds x coord to list and normalises by dividing by the function_domain 
		//so that it can be used immediatly by OpenGL
		flat_coords.push_back(float(i / function_domain));
		//Calculates Y coord of sine by turning the x value into radians 
		//using a custom defined PI value and then using the math sin function to calculate a y value
		//the sine function uses radians so the degrees value has to be * by PI and / by 180 to get radians
		flat_coords.push_back(float(sin((i*PI) / 180.0f)));
		//Adds a z coordiante of 0.0f for now as we only want 2D however can be changed later for 3D waves.
		flat_coords.push_back(0.0f);
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
