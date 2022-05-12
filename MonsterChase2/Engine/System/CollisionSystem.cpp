#include "CollisionSystem.h"
#include "../SmartPointer/SmartPointer.h"
#include "../Object/GameObject.h"
#include "../Component/BoxCollider2D.h"
#include "../GameWorld.h"
#include <algorithm>
#include <iterator>
#include <Windows.h>

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
			if (doesIntersect)
			{
#ifdef _DEBUG
				const size_t	lenBuffer = 65;
				char			Buffer[lenBuffer];
				sprintf_s(Buffer, lenBuffer, "Collision Detected\n");
				OutputDebugStringA(Buffer);
#endif // __DEBUG
			}
		}
	}
}

bool CollisionSystem::DoesInterect(BoxCollider2D& A, BoxCollider2D& B)
{
	for (const Vector4& AAxis : A.GetWorldExtentAxes())
	{
		std::vector<float> projectionValues;
		for (const Vector4& currentVertex : A.GetWorldExtentCoordinates()) {
			//TODO: Dot product	
			float axisProjection = Vector4::DotProduct(AAxis, currentVertex);
			projectionValues.push_back(axisProjection);
		}
		//TODO: Get the Min & Max
		float aMinimumProjection = *std::min_element(projectionValues.begin(), projectionValues.end());
		float aMaximumProjection = *std::min_element(projectionValues.begin(), projectionValues.end());

		projectionValues.clear();

		for (const Vector4& currentVertex : B.GetWorldExtentCoordinates()) {
			//TODO: Dot product
			float axisProjection = Vector4::DotProduct(AAxis, currentVertex);
			projectionValues.push_back(axisProjection);
		}
		// TODO: Get the Min & Max
		float bMinimumProjection = *std::min_element(projectionValues.begin(), projectionValues.end());
		float bMaximumProjection = *std::min_element(projectionValues.begin(), projectionValues.end());

		projectionValues.clear();

		//TODO: Check the min and max to determine possible intersection
		if ((aMinimumProjection < bMaximumProjection && aMinimumProjection > bMinimumProjection)
			|| (bMinimumProjection < aMaximumProjection && bMinimumProjection > aMinimumProjection)) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}
