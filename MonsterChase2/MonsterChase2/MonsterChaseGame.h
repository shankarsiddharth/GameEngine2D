#pragma once

#include "GameRuntime.h"
#include "SmartPointer/SmartPointer.h"
#include "Object/ObjectGenerator.h"
#include "Object/GameObject.h"
#include "FileLoader/JSONParser.h"

class Sprite2D;
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

	SharedPointer<GameObject> player;
	Sprite2D* playerSprite;
	RigidBody2D* playerRigidBody;

	SharedPointer<GameObject> monster;
	Sprite2D* monsterSprite;

	ObjectGenerator objectGenerator;
	JSONParser jsonParser;		
};

