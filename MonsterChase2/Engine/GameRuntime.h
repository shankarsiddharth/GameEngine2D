#pragma once

#include "GameEngine.h"
#include "GameWindow.h"

class GameRuntime
{
public:
	bool Initialize(HINSTANCE i_hInstance, int i_nCmdShow);
	void UpdateInput();
	void Update();
	void ShutDown();

	bool IsRunning();
	void UpdateDeltaTime();

private:
	bool bQuit = false;

	float deltaTime;
	GameEngine gameEngine;
	GameWindow gameWindow;
};

