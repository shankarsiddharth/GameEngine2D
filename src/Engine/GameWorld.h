#pragma once
#include <vector>
#include "SmartPointer/SmartPointer.h"

class GameObject;

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void AddGameObject(SharedPointer<GameObject> InGameObject);
	void RemoveGameObject(SharedPointer<GameObject> InGameObject);
	void RemoveGameObjectAtIndex(size_t InIndex);
	std::vector<SharedPointer<GameObject>> GetAllGameObjects();

	SharedPointer<GameObject> GetGameObjectAtIndex(size_t InIndex);

	size_t GetGameObjectsCount();

	void Initialize();
	void Update();
	void ShutDown();

private:

	std::vector<SharedPointer<GameObject>> m_GameObjectList;
};

