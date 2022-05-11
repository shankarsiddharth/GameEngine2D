#include "GameEngine.h"
#include <stdio.h>
#include "Time/EngineTime.h"
#include "GameWorld.h"


void GameEngine::Initialize()
{
	printf("Engine is Initialized.\n");

	//Initialize Time
	EngineTime::Initialize();
	physicsSystem.Initialize();
	renderSystem.Initialize();
	collisionSystem.Initialize();
}

void GameEngine::Update(float deltaTime, GameWorld* i_GameWorld)
{
	physicsSystem.Update(deltaTime, i_GameWorld);
	renderSystem.Update(deltaTime, i_GameWorld);
	collisionSystem.Update(deltaTime, i_GameWorld);
}

void GameEngine::ShutDown()
{
	collisionSystem.ShutDown();
	physicsSystem.ShutDown();
	renderSystem.ShutDown();
}

float GameEngine::ComputeDeltaTime()
{
	return EngineTime::GetFrameTime();
}
