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
		playerRigidBody->AddForce(Vector2(2.5f, 2.5f));
	}
}

void MonsterChaseGame::LoadGameObjects()
{
	player = SharedPointer<GameObject>(new GameObject());
	playerSprite = new Sprite2D(player.AccessPointer(), "data\\player.dds");
	player->AddComponent(playerSprite);
	playerRigidBody = new RigidBody2D(player.AccessPointer(), 0.5f);
	player->AddComponent(playerRigidBody);
	//World::GetInstance().AddGameObject(player);
	gameWorld.AddGameObject(player.AccessPointer());
	
	monster = SharedPointer<GameObject>(new GameObject());
	monsterSprite = new Sprite2D(monster.AccessPointer(), "data\\monster.dds");
	monster->AddComponent(monsterSprite);
	//World::GetInstance().AddGameObject(monster);
	gameWorld.AddGameObject(monster.AccessPointer());
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
