#include "CollisionSystem.h"
#include "../SmartPointer/SmartPointer.h"
#include "../Object/GameObject.h"
#include "../Component/BoxCollider2D.h"
#include "../GameWorld.h"
#include <algorithm>
#include <iterator>
#include <Windows.h>
#include "../Helpers/EngineHelpers.h"
#include "../Component/RigidBody2D.h"

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

	SeparatingAxisCheck(boxColliders, deltaTime);

}

void CollisionSystem::ShutDown()
{

}

void CollisionSystem::SeparatingAxisCheck(const std::vector<BoxCollider2D*>& InBoxColliderList, float deltaTime)
{
	for (size_t i = 0; i < InBoxColliderList.size(); i++)
	{
		for (size_t j = 0; j < InBoxColliderList.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			BoxCollider2D& colliderA = *(InBoxColliderList[i]);
			BoxCollider2D& colliderB = *(InBoxColliderList[j]);

			bool doesIntersect = DoesInterect(colliderA, colliderB, deltaTime) && DoesInterect(colliderB, colliderA, deltaTime);
			if (doesIntersect)
			{
				EngineHelpers::DebugPrint("Collision Detected");
				colliderA.ExecuteCollisionCallback(colliderB.GetRootGameObject());
			}
		}
	}
}

bool CollisionSystem::DoesInterect(BoxCollider2D& A, BoxCollider2D& B, float deltaTime)
{
	for (const Vector4& AAxis : A.GetWorldExtentAxes())
	{
		std::vector<float> projectionValues;
		for (const Vector4& currentVertex : A.GetWorldExtentCoordinates()) {
			//Dot product	
			float axisProjection = Vector4::DotProduct(AAxis, currentVertex);
			projectionValues.push_back(axisProjection);
		}
		//Get the Min & Max
		float aMinimumProjection = *std::min_element(projectionValues.begin(), projectionValues.end());
		float aMaximumProjection = *std::max_element(projectionValues.begin(), projectionValues.end());

		projectionValues.clear();

		for (const Vector4& currentVertex : B.GetWorldExtentCoordinates()) {
			//Dot product
			float axisProjection = Vector4::DotProduct(AAxis, currentVertex);
			projectionValues.push_back(axisProjection);
		}
		//Get the Min & Max
		float bMinimumProjection = *std::min_element(projectionValues.begin(), projectionValues.end());
		float bMaximumProjection = *std::max_element(projectionValues.begin(), projectionValues.end());

		projectionValues.clear();

		//Check the min and max to determine possible intersection
		if ((aMinimumProjection < bMaximumProjection && aMinimumProjection > bMinimumProjection)
			|| (bMinimumProjection < aMaximumProjection && bMinimumProjection > aMinimumProjection)) {
			//Projections Overlap, Check for Other Axes
			continue;
		}
		else {
			//Check for swept axis
			//Find the distance between the projections
			float distanceAB = 0.0f;
			if (bMaximumProjection <= aMinimumProjection)
			{
				distanceAB = aMinimumProjection - bMaximumProjection;
			}
			else if (aMaximumProjection <= bMinimumProjection)
			{
				distanceAB = bMinimumProjection - aMaximumProjection;
			}
			if (A.GetRootGameObject()->GetComponent<RigidBody2D>()
				&& B.GetRootGameObject()->GetComponent<RigidBody2D>())
			{
				Vector2 VelocityA = A.GetRootGameObject()->GetComponent<RigidBody2D>()->GetVelocity();
				Vector2 VelocityB = B.GetRootGameObject()->GetComponent<RigidBody2D>()->GetVelocity();
				//Calculate Relative Velocity
				Vector4 relativeVelocity = Vector4(VelocityA, 0, 1) - Vector4(VelocityB, 0, 1);
				float projectedVelocityOnAxis = Vector4::DotProduct(AAxis, relativeVelocity);
				//Calculate time to close the distance between the A & B projections
				float timeToClose = distanceAB / projectedVelocityOnAxis;
				if (timeToClose >= 0 && timeToClose < deltaTime)
				{
					return true;
				}
			}			
			return false;
		}
	}
	return true;
}
