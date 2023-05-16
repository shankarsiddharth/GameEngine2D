#include "InputHelpers.h"
#include <stdio.h>

bool InputHelpers::ReadInteger(int& OutInteger, int InMinimumValue)
{
	int is_valid_input = scanf_s("%d", &OutInteger);
	if (is_valid_input == EOF)
	{
		return false;
	}
	else if (is_valid_input == 0)
	{
		return false;
	}
	else if (OutInteger < InMinimumValue)
	{
		return false;
	}
	return true;
}