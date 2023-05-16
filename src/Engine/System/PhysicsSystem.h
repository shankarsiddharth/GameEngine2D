#pragma once

class GameWorld;

class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void Initialize();
	void Update(float InDeltaTime, GameWorld* InGameWorld);
	void ShutDown();

};

