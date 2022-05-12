#pragma once
#include <vector>
#include "SmartPointer/SmartPointer.h"

class GameObject;

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void AddGameObject(SharedPointer<GameObject> i_GameObject);
	void RemoveGameObject(SharedPointer<GameObject> i_GameObject);
	void RemoveGameObjectAtIndex(size_t i_Index);
	std::vector<SharedPointer<GameObject>> GetAllGameObjects();

	SharedPointer<GameObject> GetGameObjectAtIndex(size_t i_Index);

	size_t GetGameObjectsCount();

	void Initialize();
	void Update();
	void ShutDown();

private:

	std::vector<SharedPointer<GameObject>> gameObjectList;
};

