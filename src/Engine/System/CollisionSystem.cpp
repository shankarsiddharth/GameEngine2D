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

void CollisionSystem::Update(float InDeltaTime, GameWorld* InGameWorld)
{
	//Get All Colliders from the GameWorld
	std::vector<BoxCollider2D*> boxColliders;
	std::vector<SharedPointer<GameObject>> gameObjects = InGameWorld->GetAllGameObjects();
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

	SeparatingAxisCheck(boxColliders, InDeltaTime);

}

void CollisionSystem::ShutDown()
{

}

void CollisionSystem::ListenForCollisions(FOnCollisionDetected InOnCollisionDetectedCallback)
{
	if (InOnCollisionDetectedCallback != nullptr)
	{
		m_OnCollisionDetected = InOnCollisionDetectedCallback;
	}
}

void CollisionSystem::SeparatingAxisCheck(const std::vector<BoxCollider2D*>& InBoxColliderList, float InDeltaTime)
{
	for (size_t i = 0; i < InBoxColliderList.size(); i++)
	{
		for (size_t j = 0; j < InBoxColliderList.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			if (InBoxColliderList[i] != nullptr && InBoxColliderList[j] != nullptr)
			{
				BoxCollider2D& colliderA = *(InBoxColliderList[i]);
				BoxCollider2D& colliderB = *(InBoxColliderList[j]);

				bool doesIntersectAB = DoesInterect(colliderA, colliderB, InDeltaTime);
				bool doesIntersectBA = DoesInterect(colliderB, colliderA, InDeltaTime);
				if (doesIntersectAB && doesIntersectBA)
				{
					EngineHelpers::DebugPrint("Collision Detected");
					if (m_OnCollisionDetected != nullptr)
					{
						m_OnCollisionDetected(colliderA.GetRootGameObject(), colliderB.GetRootGameObject());
					}
					if (InBoxColliderList[i] != nullptr && InBoxColliderList[j] != nullptr)
					{
						colliderA.ExecuteCollisionCallback(colliderB.GetRootGameObject());
					}
				}
			}
		}
	}
}

bool CollisionSystem::DoesInterect(BoxCollider2D& InA, BoxCollider2D& InB, float InDeltaTime)
{
	for (const Vector4& AAxis : InA.GetWorldExtentAxes())
	{
		std::vector<float> projectionValues;
		for (const Vector4& currentVertex : InA.GetWorldExtentCoordinates()) {
			//Dot product	
			float axisProjection = Vector4::DotProduct(AAxis, currentVertex);
			projectionValues.push_back(axisProjection);
		}
		//Get the Min & Max
		float aMinimumProjection = *std::min_element(projectionValues.begin(), projectionValues.end());
		float aMaximumProjection = *std::max_element(projectionValues.begin(), projectionValues.end());

		projectionValues.clear();

		for (const Vector4& currentVertex : InB.GetWorldExtentCoordinates()) {
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
			if (InA.GetRootGameObject()->GetComponent<RigidBody2D>()
				&& InB.GetRootGameObject()->GetComponent<RigidBody2D>())
			{
				Vector2 VelocityA = InA.GetRootGameObject()->GetComponent<RigidBody2D>()->GetVelocity();
				Vector2 VelocityB = InB.GetRootGameObject()->GetComponent<RigidBody2D>()->GetVelocity();
				//Calculate Relative Velocity
				Vector4 relativeVelocity = Vector4(VelocityA, 0, 1) - Vector4(VelocityB, 0, 1);
				float projectedVelocityOnAxis = Vector4::DotProduct(AAxis, relativeVelocity);
				//Calculate time to close the distance between the A & B projections
				float timeToClose = distanceAB / projectedVelocityOnAxis;
				if (timeToClose >= 0 && timeToClose < InDeltaTime)
				{
					return true;
				}
			}
			return false;
		}
	}
	return true;
}
