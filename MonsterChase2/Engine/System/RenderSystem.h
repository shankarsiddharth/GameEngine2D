#pragma once

class GameWorld;

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void Initialize();
	void Update(float deltaTime, GameWorld* i_GameWorld);
	void ShutDown();

private:
	void BeginRendering();
	void EndRendering();
};

