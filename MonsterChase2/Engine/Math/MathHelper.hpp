#pragma once

#include <cstdlib>

inline int GetRandomNumberInRange(int upper = INT_MAX, int lower = INT_MIN)
{
	int number = (std::rand() % (upper - lower + 1)) + lower;
	return number;
}
