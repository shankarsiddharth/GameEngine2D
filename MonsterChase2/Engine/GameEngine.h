#pragma once

#include "System/RenderSystem.h"

class GameEngine
{
public:
	void Initialize();
	void Update(float deltaTime);
	void ShutDown();

	float ComputeDeltaTime();

private:
	RenderSystem renderSystem;
};