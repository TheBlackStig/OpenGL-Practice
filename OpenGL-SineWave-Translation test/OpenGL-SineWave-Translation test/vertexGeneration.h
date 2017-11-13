#pragma once

#include <iostream>

#include <string>

#include <vector>

#include <math.h>

//Defines cosntant PI
#define PI 3.1451926539
//Defines a class for a single sinewave
class sineWave {
	private:
		std::vector<float> verticies;
	public:
		std::vector<float> verticiesReturn() { return verticies; }
		std::vector<float> verticiesEnter(std::vector<float> in_vector) { verticies = in_vector; }
		
};

//Identifer for function to genreate a sine wave
std::vector<float> sineWaveGenerator(float x_offset, float y_offset, float z_offset);