#pragma once

class GameWorld;

class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void Initialize();
	void Update(float deltaTime, GameWorld* i_GameWorld);
	void ShutDown();

};

