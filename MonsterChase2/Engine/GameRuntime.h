#pragma once

#include "GameEngine.h"
#include "GameWindow.h"
#include "GameWorld.h"

class GameRuntime
{
public:
	GameRuntime();
	~GameRuntime();

	bool Initialize(HINSTANCE i_hInstance, int i_nCmdShow);
	void UpdateInput();
	void Update();
	void ShutDown();

	bool IsRunning();
	void UpdateDeltaTime();

protected:
	bool bQuit = false;

	float deltaTime;
	GameEngine gameEngine;
	GameWindow gameWindow;
	GameWorld gameWorld;
};

