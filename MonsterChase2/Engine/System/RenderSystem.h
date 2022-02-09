#pragma once

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void Initialize();
	void Update(float deltaTime);
	void ShutDown();

private:
	void BeginRendering();
	void EndRendering();
};

