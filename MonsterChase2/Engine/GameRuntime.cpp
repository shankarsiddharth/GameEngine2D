#include "GameRuntime.h"

GameRuntime::GameRuntime()
	:m_DeltaTime(1/60.0f)
{

}

GameRuntime::~GameRuntime()
{

}

bool GameRuntime::Initialize(HINSTANCE InHInstance, int InNCmdShow)
{
	bool isWindowInitialized = m_GameWindow.Initialize(InHInstance, InNCmdShow);
	if (isWindowInitialized)
	{
		m_InputSystem.Initialize();
		m_GameWorld.Initialize();
		m_GameEngine.Initialize();
		return true;
	}
	return false;
}

void GameRuntime::UpdateInput()
{
	/*if (inputSystem.IsValidInput())
	{
		ProcessInput();
		inputSystem.ClearInput();
	}*/
	ProcessInput();
	m_InputSystem.ClearInput();
	m_InputSystem.UpdateInput();
}

void GameRuntime::Update()
{
	m_GameWindow.Update();
	if (!m_GameWindow.IsWindowClosed())
	{
		m_GameWorld.Update();
		m_GameEngine.Update(m_DeltaTime, &m_GameWorld);
	}
}

void GameRuntime::ShutDown()
{
	m_GameEngine.ShutDown();
	m_GameWorld.ShutDown();
	m_GameWindow.ShutDown();
}

bool GameRuntime::IsRunning()
{
	return !m_GameWindow.IsWindowClosed();
}

void GameRuntime::UpdateDeltaTime()
{
	m_DeltaTime = m_GameEngine.ComputeDeltaTime();
}

void GameRuntime::ProcessInput()
{

}
