#include "CollisionSystem.h"
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
			boxCollider2DComponent->UpdateWorldExtentsAxes();
			boxColliders.push_back(boxCollider2DComponent);
		}
	}

	SeparatingAxisCheck(boxColliders);

}

void CollisionSystem::ShutDown()
{

}

void CollisionSystem::SeparatingAxisCheck(const std::vector<BoxCollider2D*>& InBoxColliderList)
{
	for (int i = 0; i < InBoxColliderList.size(); i++)
	{
		for (int j = 0; j < InBoxColliderList.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			BoxCollider2D& colliderA = *(InBoxColliderList[i]);
			BoxCollider2D& colliderB = *(InBoxColliderList[j]);

			bool doesIntersect = DoesInterect(colliderA, colliderB) && DoesInterect(colliderB, colliderA);
		}
	}
}

bool CollisionSystem::DoesInterect(BoxCollider2D& A, BoxCollider2D& B)
{
	for (const Vector4& AAxis : A.GetWorldExtentAxes())
	{
		for (const Vector4& vertex : A.GetWorldExtentCoordinates()) {
			//TODO: Dot product			
			//TODO: Get the Min & Max
		}

		for (const Vector4& vertex : B.GetWorldExtentCoordinates()) {
			//TODO: Dot product
			//TODO: Get the Min & Max
		}

		//TODO: Check the min and max to determine possible intersection
	}
	return false;
}
