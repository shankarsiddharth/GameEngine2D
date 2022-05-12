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
	monsterSprite(nullptr),
	playerRigidBody(nullptr)
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
	float force = 25.0f;
	
	/*if (inputSystem.IsKeyDown(KeyCode::W))
	{
		player->GetComponent<RigidBody2D>()->AddForce(Vector2(force, 0));
	}
	if (inputSystem.IsKeyDown(KeyCode::A))
	{
		player->GetComponent<RigidBody2D>()->AddForce(Vector2(0, -force));
	}
	if (inputSystem.IsKeyDown(KeyCode::S))
	{
		player->GetComponent<RigidBody2D>()->AddForce(Vector2(-force, 0));
	}
	if (inputSystem.IsKeyDown(KeyCode::D))
	{
		player->GetComponent<RigidBody2D>()->AddForce(Vector2(0, force));
	}*/

	if (inputSystem.IsKeyPressed(KeyCode::W))
	{
		player->GetComponent<RigidBody2D>()->AddForce(Vector2(0, force));
	}
	if (inputSystem.IsKeyPressed(KeyCode::A))
	{
		player->GetComponent<RigidBody2D>()->AddForce(Vector2(-force, 0));
	}
	if (inputSystem.IsKeyPressed(KeyCode::S))
	{
		player->GetComponent<RigidBody2D>()->AddForce(Vector2(0, -force));
	}
	if (inputSystem.IsKeyPressed(KeyCode::D))
	{
		player->GetComponent<RigidBody2D>()->AddForce(Vector2(force, 0));
	}

	if (inputSystem.IsKeyPressed(KeyCode::K))
	{
		player->AddRotationZ(0.01f);
	}
	if (inputSystem.IsKeyPressed(KeyCode::L))
	{
		player->AddRotationZ(-0.01f);
	}
}

void MonsterChaseGame::LoadGameObjects()
{
	player = objectGenerator.CreateGameObjectFromJSONDocument(jsonParser.GetJSONDocument("data/player.json"));
	gameWorld.AddGameObject(player);

	monster = objectGenerator.CreateGameObjectFromJSONDocument(jsonParser.GetJSONDocument("data/monster.json"));
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
