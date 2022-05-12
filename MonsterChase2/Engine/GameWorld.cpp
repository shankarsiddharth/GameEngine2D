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

void GameWorld::RemoveGameObject(SharedPointer<GameObject> i_GameObject)
{
	if (!i_GameObject) {
		return;
	}

	for (std::vector<SharedPointer<GameObject>>::iterator listIterator = gameObjectList.begin();
		listIterator != gameObjectList.end();)
	{
		if (*listIterator == i_GameObject)
		{
			(*listIterator)->RemoveAllComponents();
			listIterator = gameObjectList.erase(listIterator);
		}
		else
		{
			listIterator++;
		}
	}
}

void GameWorld::RemoveGameObjectAtIndex(size_t i_Index)
{
	/*size_t index = 0;

	for (std::vector<SharedPointer<GameObject>>::iterator listIterator = gameObjectList.begin();
		listIterator != gameObjectList.end();)
	{
		if (index == i_Index)
		{
			(*listIterator)->RemoveAllComponents();
			listIterator = gameObjectList.erase(listIterator);
		}
		else
		{
			listIterator++;
			index++;
		}
	}*/

	if (i_Index < gameObjectList.size())
	{
		SharedPointer<GameObject> gameObjectToRemove = gameObjectList.at(i_Index);
		gameObjectToRemove->RemoveAllComponents();
		gameObjectList.erase(gameObjectList.begin() + i_Index);
	}
}

std::vector<SharedPointer<GameObject>> GameWorld::GetAllGameObjects()
{
	return gameObjectList;
}

SharedPointer<GameObject> GameWorld::GetGameObjectAtIndex(size_t i_Index)
{
	if (i_Index < gameObjectList.size())
	{
		return gameObjectList.at(i_Index);
		/*for (size_t index = 0; index < gameObjectList.size(); index++)
		{
			if (index == i_Index)
			{
				return gameObjectList.at(i_Index);
			}
		}*/
	}
	else
	{
		return SharedPointer<GameObject>(nullptr);
	}
}

size_t GameWorld::GetGameObjectsCount()
{
	return gameObjectList.size();
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
