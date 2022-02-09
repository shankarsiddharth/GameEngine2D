#pragma once

#include <vector>

class GameObject;

class World
{
public:
	static World& GetInstance();

	World(World const&) = delete;
	void operator=(World const&) = delete;

	void AddGameObject(GameObject* i_GameObject);
	std::vector<GameObject*> GetAllGameObjects();

	void ShutDown();

private:
	World() = default;

	std::vector<GameObject*> gameObjectList;
};

