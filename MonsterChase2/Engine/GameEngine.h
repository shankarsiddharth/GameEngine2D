#pragma once

#include "System/RenderSystem.h"

class GameWorld;

class GameEngine
{
public:
	void Initialize();
	void Update(float deltaTime, GameWorld* i_GameWorld);
	void ShutDown();

	float ComputeDeltaTime();

private:
	RenderSystem renderSystem;
};