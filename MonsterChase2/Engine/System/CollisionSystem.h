#pragma once

class GameWorld;

class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void Initialize();
	void Update(float deltaTime, GameWorld* i_GameWorld);
	void ShutDown();

};

