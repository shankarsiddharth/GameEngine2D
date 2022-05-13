#pragma once

#include "GameRuntime.h"

class Game :
	public GameRuntime
{
public:
	Game();
	~Game();

	void StartGame(HINSTANCE i_hInstance, int i_nCmdShow);
	
protected:
	virtual void ProcessInput() = 0;
	virtual void InitializeGameplay() = 0;
	virtual void StartGameplay() = 0;
	virtual void UpdateGameplay() = 0;
	virtual void ShutDownGameplay() = 0;

private:
	void UpdateGame();
	void ExitGame();

};

