#include "MathHelper.h"

int MathHelper::GetRandomNumberInRange(int InUpperLimit /*= INT_MAX*/, int InLowerLimit /*= INT_MIN*/)
{
	int number = (std::rand() % (InUpperLimit - InLowerLimit + 1)) + InLowerLimit;
	return number;
}
