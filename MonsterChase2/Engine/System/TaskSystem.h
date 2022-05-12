#pragma once

class GameWorld;

class TaskSystem
{
public:
	TaskSystem();
	~TaskSystem();

	void Initialize();
	void Update(float deltaTime, GameWorld* i_GameWorld);
	void ShutDown();

private:

};