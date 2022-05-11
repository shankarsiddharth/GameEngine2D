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
	std::vector<SharedPointer<GameObject>> GetAllGameObjects();

	void Initialize();
	void Update();
	void ShutDown();

private:

	std::vector<SharedPointer<GameObject>> gameObjectList;
};

