#include "GameRuntime.h"

GameRuntime::GameRuntime()
	:deltaTime(1/60.0f)
{

}

GameRuntime::~GameRuntime()
{

}

bool GameRuntime::Initialize(HINSTANCE i_hInstance, int i_nCmdShow)
{
	bool isWindowInitialized = gameWindow.Initialize(i_hInstance, i_nCmdShow);
	if (isWindowInitialized)
	{
		gameWorld.Initialize();
		gameEngine.Initialize();
		return true;
	}
	return false;
}

void GameRuntime::UpdateInput()
{

}

void GameRuntime::Update()
{
	gameWindow.Update();
	if (!gameWindow.IsWindowClosed())
	{
		gameWorld.Update();
		gameEngine.Update(deltaTime, &gameWorld);
	}
}

void GameRuntime::ShutDown()
{
	gameEngine.ShutDown();
	gameWorld.ShutDown();
	gameWindow.ShutDown();
}

bool GameRuntime::IsRunning()
{
	return !gameWindow.IsWindowClosed();
}

void GameRuntime::UpdateDeltaTime()
{
	deltaTime = gameEngine.ComputeDeltaTime();
}
