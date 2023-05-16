#include "EngineHelpers.h"

void EngineHelpers::DebugPrint(std::string InDebugLogString)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 500;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "%s\n", InDebugLogString.c_str());

	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

