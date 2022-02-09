#pragma once
#include <vector>

class GameObject;

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void AddGameObject(GameObject* i_GameObject);
	std::vector<GameObject*> GetAllGameObjects();

	void Initialize();
	void Update();
	void ShutDown();

private:

	std::vector<GameObject*> gameObjectList;
};

