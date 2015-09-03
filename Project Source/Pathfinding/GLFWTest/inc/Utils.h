// Author: Shane Coates
// Description: Simple utility functions

#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdlib.h>
#include <iostream>
#include <random>

class Utils
{
public:


	static int RandomNumber(int min, int max)
	{	
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(min, max);
		return (dist(mt));
		//return min + static_cast<T>(rand()) / static_cast<T> (RAND_MAX / (max - min));
	}
};

#endif

