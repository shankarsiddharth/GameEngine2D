#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

namespace EngineTime
{

	LARGE_INTEGER intToLargeInt(uint64_t i);

	uint64_t GetCurrentTickCounter();

	float GetTimeDiff_ms(uint64_t InStartTime, uint64_t InEndTime = GetCurrentTickCounter());

	float GetFrameTime();

	void Initialize();
}