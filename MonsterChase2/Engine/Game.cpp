#include "Game.h"

Game::Game()
	:GameRuntime()
{
	
}

Game::~Game()
{
	
}

void Game::StartGame(HINSTANCE i_hInstance, int i_nCmdShow)
{
	InitializeGameplay();
	bool isRuntimeInitialized = Initialize(i_hInstance, i_nCmdShow);
	if (isRuntimeInitialized)
	{
		StartGameplay();
		UpdateGame();
		ExitGame();
	}
}

void Game::UpdateGame()
{
	do
	{
		UpdateDeltaTime();
		Update();
		UpdateInput();
		UpdateGameplay();
	} while (IsRunning());
}

void Game::ExitGame()
{
	ShutDownGameplay();
	ShutDown();
}
