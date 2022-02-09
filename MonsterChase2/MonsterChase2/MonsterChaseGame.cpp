#include "MonsterChaseGame.h"
#include "Object/GameObject.h"
#include "Component/Sprite2D.h"
#include "GameRuntime.h"
#include "Component/RigidBody2D.h"

MonsterChaseGame::MonsterChaseGame()
	:GameRuntime(),
	player(nullptr),
	playerSprite(nullptr),
	monster(nullptr),
	monsterSprite(nullptr)
{

}

MonsterChaseGame::~MonsterChaseGame()
{
	/*if (playerSprite != nullptr)
	{
		delete playerSprite;
		playerSprite = nullptr;
	}

	if (monsterSprite != nullptr)
	{
		delete monsterSprite;
		monsterSprite = nullptr;
	}*/
	/*if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	if (monster != nullptr)
	{
		delete monster;
		monster = nullptr;
	}*/
}

void MonsterChaseGame::StartGame(HINSTANCE i_hInstance, int i_nCmdShow)
{
	bool isRuntimeInitialized = Initialize(i_hInstance, i_nCmdShow);
	if (isRuntimeInitialized)
	{
		LoadGameObjects();
		UpdateGame();
		ExitGame();
	}
}

void MonsterChaseGame::ProcessInput()
{
	/*if (inputSystem.GetCurrentKeyCode() == KeyCode::A)
	{
		int a = 0;
	}*/
	if (inputSystem.IsKeyDown(KeyCode::A))
	{
		int a = 0;
		playerRigidBody->AddForce(Vector2(1.5f, 1.5f));
	}
}

void MonsterChaseGame::LoadGameObjects()
{
	player = new GameObject();
	playerSprite = new Sprite2D(player, "data\\player.dds");
	player->AddComponent(playerSprite);
	playerRigidBody = new RigidBody2D(player);
	player->AddComponent(playerRigidBody);
	//World::GetInstance().AddGameObject(player);
	gameWorld.AddGameObject(player);
	
	monster = new GameObject();
	monsterSprite = new Sprite2D(monster, "data\\monster.dds");
	monster->AddComponent(monsterSprite);
	//World::GetInstance().AddGameObject(monster);
	gameWorld.AddGameObject(monster);
}

void MonsterChaseGame::UpdateGame()
{
	do
	{
		UpdateDeltaTime();
		UpdateInput();
		Update();
	} while (IsRunning());
}

void MonsterChaseGame::ExitGame()
{
	ShutDown();
}
