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

	bool Initialize(HINSTANCE InHInstance, int InNCmdShow);
	void UpdateInput();
	void Update();
	void ShutDown();

	bool IsRunning();
	void UpdateDeltaTime();

	virtual void ProcessInput() = 0;

protected:
	bool m_ShouldQuit = false;

	float m_DeltaTime;
	GameEngine m_GameEngine;
	GameWindow m_GameWindow;
	GameWorld m_GameWorld;
	InputSystem m_InputSystem;
};

