#pragma once

class GameWorld;

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void Initialize();
	void Update(float InDeltaTime, GameWorld* InGameWorld);
	void ShutDown();

private:
	void BeginRendering();
	void EndRendering();
};

