#include "TaskSystem.h"
#include "../JobSystem/JobSystem/JobSystem.h"
#include "../GameWorld.h"

TaskSystem::~TaskSystem()
{

}

void TaskSystem::Initialize()
{
	Engine::JobSystem::Init();
}

void TaskSystem::Update(float InDeltaTime, GameWorld* InGameWorld)
{

}

void TaskSystem::ShutDown()
{
	Engine::JobSystem::RequestShutdown();
}

TaskSystem::TaskSystem()
{

}

