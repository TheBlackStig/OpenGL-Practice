#include "vertexGeneration.h"

//A function for generating coordinates of a sine wave

std::vector<float> sineWaveGenerator(float x_offset, float y_offset, float z_offset)
{
	std::vector<float> sine_wave_verticies;
	float function_domain = 360;
	for (int i = -function_domain; i <= function_domain; i++)
	{
		sine_wave_verticies.push_back((i / function_domain) + x_offset);
		sine_wave_verticies.push_back((sin(((i / function_domain) * PI) / 180)) + y_offset);
		sine_wave_verticies.push_back(z_offset);
	}

	return sine_wave_verticies;
}