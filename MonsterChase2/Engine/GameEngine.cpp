#include "GameEngine.h"
#include <stdio.h>
#include "Time/EngineTime.h"
#include "GameWorld.h"


void GameEngine::Initialize()
{
	printf("Engine is Initialized.\n");

	//Initialize Time
	EngineTime::Initialize();

	renderSystem.Initialize();
}

void GameEngine::Update(float deltaTime, GameWorld* i_GameWorld)
{
	renderSystem.Update(deltaTime, i_GameWorld);
}

void GameEngine::ShutDown()
{
	renderSystem.ShutDown();
}

float GameEngine::ComputeDeltaTime()
{
	return EngineTime::GetFrameTime();
}
