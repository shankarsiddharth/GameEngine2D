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

void RenderSystem::Update(float InDeltaTime, GameWorld* InGameWorld)
{
	BeginRendering();

	//std::vector<GameObject*> gameObjects = World::GetInstance().GetAllGameObjects();
	std::vector<SharedPointer<GameObject>> gameObjects = InGameWorld->GetAllGameObjects();
	for (SharedPointer<GameObject> gameObject : gameObjects)
	{
		if (gameObject->IsVisible())
		{
			GLib::Point2D position{ (float)(gameObject->GetPosition().X()), (float)(gameObject->GetPosition().Y()) };
			Sprite2D* spriteComponent = gameObject->GetComponent<Sprite2D>();
			if (spriteComponent != nullptr)
			{
				float rotationZ = gameObject->GetRotation().Z();
				GLib::Render(*(spriteComponent->GetGLibSprite()), position, 0.0f, rotationZ);
			}
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
	GLib::BeginRendering(DirectX::Colors::Black);
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
