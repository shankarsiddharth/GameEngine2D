#include "GameEngine.h"
#include <stdio.h>
#include "Time/EngineTime.h"


void GameEngine::Initialize()
{
	printf("Engine is Initialized.\n");

	//Initialize Time
	EngineTime::Initialize();

	renderSystem.Initialize();
}

void GameEngine::Update(float deltaTime)
{
	renderSystem.Update(deltaTime);
}

void GameEngine::ShutDown()
{
	renderSystem.ShutDown();
}

float GameEngine::ComputeDeltaTime()
{
	return EngineTime::GetFrameTime();
}
