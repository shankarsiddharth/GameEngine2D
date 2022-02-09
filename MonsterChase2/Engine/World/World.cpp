#include "World.h"
#include "../Object/GameObject.h"

World& World::GetInstance()
{
	static World INSTANCE;
	return INSTANCE;
}

void World::AddGameObject(GameObject* i_GameObject)
{
	gameObjectList.push_back(i_GameObject);
}

std::vector<GameObject*> World::GetAllGameObjects()
{
	return gameObjectList;
}

void World::ShutDown()
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
