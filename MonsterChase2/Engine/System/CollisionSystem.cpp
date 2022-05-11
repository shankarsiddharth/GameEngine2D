#include "CollisionSystem.h"
#include <vector>
#include "../SmartPointer/SmartPointer.h"
#include "../Object/GameObject.h"
#include "../Component/BoxCollider2D.h"
#include "../GameWorld.h"

CollisionSystem::CollisionSystem()
{

}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::Initialize()
{

}

void CollisionSystem::Update(float deltaTime, GameWorld* i_GameWorld)
{
	//Get All Colliders from the GameWorld
	std::vector<BoxCollider2D*> boxColliders;
	std::vector<SharedPointer<GameObject>> gameObjects = i_GameWorld->GetAllGameObjects();
	for (SharedPointer<GameObject> gameObject : gameObjects)
	{
		BoxCollider2D* boxCollider2DComponent = gameObject->GetComponent<BoxCollider2D>();
		if (boxCollider2DComponent != nullptr)
		{
			//Update the collider extents based on the object position & rotation
			boxCollider2DComponent->UpdateWorldExtents();
			boxColliders.push_back(boxCollider2DComponent);
		}
	}


}

void CollisionSystem::ShutDown()
{

}

