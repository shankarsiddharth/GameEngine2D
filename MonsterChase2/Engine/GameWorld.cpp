#include "GameWorld.h"
#include "Object/GameObject.h"

GameWorld::GameWorld()
{

}

GameWorld::~GameWorld()
{

}

void GameWorld::AddGameObject(GameObject* i_GameObject)
{
	gameObjectList.push_back(i_GameObject);
}

std::vector<GameObject*> GameWorld::GetAllGameObjects()
{
	return gameObjectList;
}

void GameWorld::Initialize()
{

}

void GameWorld::Update()
{

}

void GameWorld::ShutDown()
{
	for (GameObject* gameObject : gameObjectList)
	{
		if (gameObject != nullptr)
		{
			delete gameObject;
			gameObject = nullptr;
		}
	}
	gameObjectList.clear();
}
