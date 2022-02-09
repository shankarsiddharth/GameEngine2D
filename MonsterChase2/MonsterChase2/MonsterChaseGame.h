#pragma once

#include "GameRuntime.h"

class Sprite2D;
class GameObject;

class MonsterChaseGame :
	public GameRuntime
{
public:
	MonsterChaseGame();
	~MonsterChaseGame();

	void StartGame(HINSTANCE i_hInstance, int i_nCmdShow);
	
private:
	void UpdateGame();
	void ExitGame();

	void LoadGameObjects();

	GameObject* player;
	Sprite2D* playerSprite;
	GameObject* monster;
	Sprite2D* monsterSprite;
};

