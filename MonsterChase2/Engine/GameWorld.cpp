#include "GameWorld.h"
#include "Object/GameObject.h"

GameWorld::GameWorld()
{

}

GameWorld::~GameWorld()
{

}

void GameWorld::AddGameObject(SharedPointer<GameObject> i_GameObject)
{
	gameObjectList.push_back(i_GameObject);
}

std::vector<SharedPointer<GameObject>> GameWorld::GetAllGameObjects()
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
	for (SharedPointer<GameObject> gameObject : gameObjectList)
	{
		if (gameObject)
		{
			gameObject->RemoveAllComponents();
		}
	}
	gameObjectList.clear();
}
