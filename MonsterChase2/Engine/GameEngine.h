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
	void Update(float InDeltaTime, GameWorld* InGameWorld);
	void ShutDown();

	float ComputeDeltaTime();

	void ListenForCollisions(FOnCollisionDetected InOnCollisionDetectedCallback);

private:
	RenderSystem m_RenderSystem;
	PhysicsSystem m_PhysicsSystem;
	CollisionSystem m_CollisionSystem;
	TaskSystem m_TaskSystem;
};