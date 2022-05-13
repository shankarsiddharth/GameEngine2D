#pragma once

class GameWorld;

class TaskSystem
{
public:
	TaskSystem();
	~TaskSystem();

	void Initialize();
	void Update(float InDeltaTime, GameWorld* InGameWorld);
	void ShutDown();

private:

};