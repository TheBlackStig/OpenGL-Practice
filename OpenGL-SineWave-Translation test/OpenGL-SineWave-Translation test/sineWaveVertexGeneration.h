#pragma once

#include <iostream>

#include <string>

#include <vector>

#include <math.h>

//Defines a class for a single sinewave
class sineWave {
	private:
		std::vector<float> verticies;
	public:
		std::vector<float> verticiesReturn() { return verticies; }
		std::vector<float> verticiesEnter(std::vector<float> in_vector) { verticies = in_vector; }

};