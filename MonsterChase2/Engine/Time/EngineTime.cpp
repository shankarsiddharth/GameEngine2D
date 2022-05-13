#include "EngineTime.h"

LARGE_INTEGER PerformanceFrequency = { 0 };

LARGE_INTEGER EngineTime::intToLargeInt(uint64_t InInt)
{
	LARGE_INTEGER LI;
	LI.QuadPart = InInt;
	return LI;
}

uint64_t EngineTime::GetCurrentTickCounter()
{
	LARGE_INTEGER CurrentFrameCounter;
	BOOL isSuccess = QueryPerformanceCounter(&CurrentFrameCounter);
	assert(isSuccess == TRUE);
	return CurrentFrameCounter.QuadPart;
}

float EngineTime::GetTimeDiff_ms(uint64_t InStartTime, uint64_t InEndTime /*= GetCurrentTickCounter()*/)
{
	assert(PerformanceFrequency.QuadPart != 0);
	return ((1000.0f * static_cast<float>(InEndTime - InStartTime)) / PerformanceFrequency.QuadPart);
}

float EngineTime::GetFrameTime()
{
	static uint64_t lastFrameStartTick = 0;
	float frameTime;
	uint64_t currentFrameStartTick = GetCurrentTickCounter();
	frameTime = (lastFrameStartTick == 0) ? (1.0f / 60.0f) : (GetTimeDiff_ms(currentFrameStartTick, lastFrameStartTick) / 1000.0f);
	lastFrameStartTick = currentFrameStartTick;
	return IsDebuggerPresent() ? (1.0f / 60.0f) : frameTime;
}

void EngineTime::Initialize()
{
	//Initialize Timer
	BOOL isSuccess = QueryPerformanceFrequency(&PerformanceFrequency);
	assert(isSuccess == TRUE);
}
