#include "MonsterChaseGame.h"
#include "Object/GameObject.h"
#include "Component/Sprite2D.h"
#include "GameRuntime.h"

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
	if (playerSprite != nullptr)
	{
		delete playerSprite;
		playerSprite = nullptr;
	}

	if (monsterSprite != nullptr)
	{
		delete monsterSprite;
		monsterSprite = nullptr;
	}
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

void MonsterChaseGame::LoadGameObjects()
{
	player = new GameObject();
	Sprite2D* playerSprite = new Sprite2D(player, "data\\player.dds");
	player->AddComponent(playerSprite);
	//World::GetInstance().AddGameObject(player);
	gameWorld.AddGameObject(player);
	
	monster = new GameObject();
	Sprite2D* monsterSprite = new Sprite2D(monster, "data\\monster.dds");
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
