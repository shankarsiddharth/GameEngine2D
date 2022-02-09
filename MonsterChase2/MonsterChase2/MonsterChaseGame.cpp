#include "MonsterChaseGame.h"
#include "Object/GameObject.h"
#include "Component/Sprite2D.h"
#include "World/World.h"

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
	GameObject* player = new GameObject();
	Sprite2D* playerSprite = new Sprite2D(player, "data\\player.dds");
	player->AddComponent(playerSprite);
	World::GetInstance().AddGameObject(player);

	GameObject* monster = new GameObject();
	Sprite2D* monsterSprite = new Sprite2D(monster, "data\\monster.dds");
	monster->AddComponent(monsterSprite);
	World::GetInstance().AddGameObject(monster);
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
	World::GetInstance().ShutDown();
	ShutDown();
}
