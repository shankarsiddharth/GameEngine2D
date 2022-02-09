#include "GameRuntime.h"

bool GameRuntime::Initialize(HINSTANCE i_hInstance, int i_nCmdShow)
{
	bool isWindowInitialized = gameWindow.Initialize(i_hInstance, i_nCmdShow);
	if (isWindowInitialized)
	{
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
		gameEngine.Update(deltaTime);
	}
}

void GameRuntime::ShutDown()
{
	gameEngine.ShutDown();
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
