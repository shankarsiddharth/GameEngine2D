#include "GameWorld.h"
#include "Object/GameObject.h"

GameWorld::GameWorld()
{

}

GameWorld::~GameWorld()
{

}

void GameWorld::AddGameObject(SharedPointer<GameObject> InGameObject)
{
	m_GameObjectList.push_back(InGameObject);
}

void GameWorld::RemoveGameObject(SharedPointer<GameObject> InGameObject)
{
	if (!InGameObject) {
		return;
	}

	for (std::vector<SharedPointer<GameObject>>::iterator listIterator = m_GameObjectList.begin();
		listIterator != m_GameObjectList.end();)
	{
		if (*listIterator == InGameObject)
		{
			(*listIterator)->RemoveAllComponents();
			listIterator = m_GameObjectList.erase(listIterator);
		}
		else
		{
			listIterator++;
		}
	}
}

void GameWorld::RemoveGameObjectAtIndex(size_t InIndex)
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

	if (InIndex < m_GameObjectList.size())
	{
		SharedPointer<GameObject> gameObjectToRemove = m_GameObjectList.at(InIndex);
		gameObjectToRemove->RemoveAllComponents();
		m_GameObjectList.erase(m_GameObjectList.begin() + InIndex);
	}
}

std::vector<SharedPointer<GameObject>> GameWorld::GetAllGameObjects()
{
	return m_GameObjectList;
}

SharedPointer<GameObject> GameWorld::GetGameObjectAtIndex(size_t InIndex)
{
	if (InIndex < m_GameObjectList.size())
	{
		return m_GameObjectList.at(InIndex);
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
	return m_GameObjectList.size();
}

void GameWorld::Initialize()
{

}

void GameWorld::Update()
{

}

void GameWorld::ShutDown()
{
	for (SharedPointer<GameObject> gameObject : m_GameObjectList)
	{
		if (gameObject)
		{
			gameObject->RemoveAllComponents();
		}
	}
	m_GameObjectList.clear();
}
