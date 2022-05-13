#pragma once

struct Counter
{
	Counter(int InSharedReference)
		:m_SharedReference(InSharedReference)
	{}

	int m_SharedReference;
};