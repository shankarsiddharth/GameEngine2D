#pragma once

struct Counter
{
	Counter(int i_SharedReference)
		:sharedReference(i_SharedReference)
	{}

	int sharedReference;
};