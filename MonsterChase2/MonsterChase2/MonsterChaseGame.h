#pragma once

#include "GameRuntime.h"

class MonsterChaseGame :
	public GameRuntime
{
public:
	void StartGame(HINSTANCE i_hInstance, int i_nCmdShow);
	
private:
	void UpdateGame();
	void ExitGame();

	void LoadGameObjects();
};

