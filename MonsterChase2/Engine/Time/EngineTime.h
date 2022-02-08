#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

LARGE_INTEGER PerformanceFrequency = { 0 };

LARGE_INTEGER intToLargeInt(uint64_t i) {
	LARGE_INTEGER LI;
	LI.QuadPart = i;
	return LI;
}

uint64_t GetCurrentTickCounter()
{
	LARGE_INTEGER CurrentFrameCounter;
	BOOL isSuccess = QueryPerformanceCounter(&CurrentFrameCounter);
	assert(isSuccess == TRUE);
	return CurrentFrameCounter.QuadPart;
}

float GetTimeDiff_ms(uint64_t i_StartTime, uint64_t i_EndTime = GetCurrentTickCounter())
{
	assert(PerformanceFrequency.QuadPart != 0);
	return ((1000.0f * static_cast<float>(i_EndTime - i_StartTime)) / PerformanceFrequency.QuadPart);
}

float GetFrameTime()
{
	static uint64_t lastFrameStartTick = 0;
	float frameTime;
	uint64_t currentFrameStartTick = GetCurrentTickCounter();
	frameTime = (lastFrameStartTick == 0) ? (1.0f / 60.0f) : (GetTimeDiff_ms(currentFrameStartTick, lastFrameStartTick) / 1000.0f);
	lastFrameStartTick = currentFrameStartTick;
	return IsDebuggerPresent() ? (1.0f / 60.0f) : frameTime;
}