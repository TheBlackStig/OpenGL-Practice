//Includes the SineWaveVertexGen.h header file

#include "SineWaveVertexGen.h"

//Defines the function sineCurveGeneration
std::vector<float> sineCurveGeneration()
{
	std::vector<float> flat_coords;
	for (int i = -360; i < 360; i++)
	{
		flat_coords.push_back(i);				//X coord
		//Calculates Y coord of sine by turning the x value into radians using a custom efined PI value and then using the math sin function 
		flat_coords.push_back(sin((i*PI)/180)); //Y coord			
	}

}