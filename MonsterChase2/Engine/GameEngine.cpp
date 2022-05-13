#include "GameEngine.h"
#include <stdio.h>
#include "Time/EngineTime.h"
#include "GameWorld.h"


void GameEngine::Initialize()
{
	printf("Engine is Initialized.\n");

	//Initialize Time
	EngineTime::Initialize();
	m_PhysicsSystem.Initialize();
	m_RenderSystem.Initialize();
	m_CollisionSystem.Initialize();
	m_TaskSystem.Initialize();
}

void GameEngine::Update(float InDeltaTime, GameWorld* InGameWorld)
{
	m_PhysicsSystem.Update(InDeltaTime, InGameWorld);
	m_RenderSystem.Update(InDeltaTime, InGameWorld);
	m_CollisionSystem.Update(InDeltaTime, InGameWorld);
	m_TaskSystem.Update(InDeltaTime, InGameWorld);
}

void GameEngine::ShutDown()
{
	m_TaskSystem.ShutDown();
	m_CollisionSystem.ShutDown();
	m_PhysicsSystem.ShutDown();
	m_RenderSystem.ShutDown();
}

float GameEngine::ComputeDeltaTime()
{
	return EngineTime::GetFrameTime();
}

void GameEngine::ListenForCollisions(FOnCollisionDetected InOnCollisionDetectedCallback)
{
	m_CollisionSystem.ListenForCollisions(InOnCollisionDetectedCallback);
}
