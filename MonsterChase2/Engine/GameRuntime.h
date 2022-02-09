#pragma once

#include "GameEngine.h"
#include "GameWindow.h"
#include "GameWorld.h"
#include "Input/InputSystem.h"

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

	virtual void ProcessInput() = 0;

protected:
	bool bQuit = false;

	float deltaTime;
	GameEngine gameEngine;
	GameWindow gameWindow;
	GameWorld gameWorld;
	InputSystem inputSystem;
};

