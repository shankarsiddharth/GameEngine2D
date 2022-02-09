#pragma once

#include "GameRuntime.h"

class Sprite2D;
class GameObject;
class RigidBody2D;

class MonsterChaseGame :
	public GameRuntime
{
public:
	MonsterChaseGame();
	~MonsterChaseGame();

	void StartGame(HINSTANCE i_hInstance, int i_nCmdShow);
	

	void ProcessInput() override;

private:
	void UpdateGame();
	void ExitGame();

	void LoadGameObjects();

	GameObject* player;
	Sprite2D* playerSprite;
	RigidBody2D* playerRigidBody;

	GameObject* monster;
	Sprite2D* monsterSprite;
};

