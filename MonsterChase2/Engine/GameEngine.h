#pragma once

#include "System/RenderSystem.h"
#include "System/PhysicsSystem.h"
#include "System/CollisionSystem.h"
#include "System/TaskSystem.h"

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
	PhysicsSystem physicsSystem;
	CollisionSystem collisionSystem;
	TaskSystem taskSystem;
};