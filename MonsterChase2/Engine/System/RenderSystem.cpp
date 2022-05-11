#include "RenderSystem.h"
#include <vector>
#include "../Object/GameObject.h"
#include "../Component/Sprite2D.h"
#include "../../GLib/GLib.h"
#include <DirectXColors.h>
#include "../GameWorld.h"

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Initialize()
{

}

void RenderSystem::Update(float deltaTime, GameWorld* i_GameWorld)
{
	BeginRendering();

	//std::vector<GameObject*> gameObjects = World::GetInstance().GetAllGameObjects();
	std::vector<SharedPointer<GameObject>> gameObjects = i_GameWorld->GetAllGameObjects();
	for (SharedPointer<GameObject> gameObject : gameObjects)
	{
		GLib::Point2D position{ (float)(gameObject->GetPosition().X()), (float)(gameObject->GetPosition().Y()) };
		Sprite2D* spriteComponent = gameObject->GetComponent<Sprite2D>();
		if (spriteComponent != nullptr)
		{
			GLib::Render(*(spriteComponent->GetGLibSprite()), position, 0.0f, 0.0f);
		}
	}

	EndRendering();
}

void RenderSystem::ShutDown()
{

}

void RenderSystem::BeginRendering()
{
	// IMPORTANT: Tell GLib that we want to start rendering
	GLib::BeginRendering(DirectX::Colors::Blue);
	// Tell GLib that we want to render some sprites
	GLib::Sprites::BeginRendering();
}

void RenderSystem::EndRendering()
{
	// Tell GLib we're done rendering sprites
	GLib::Sprites::EndRendering();
	// IMPORTANT: Tell GLib we're done rendering
	GLib::EndRendering();
}
