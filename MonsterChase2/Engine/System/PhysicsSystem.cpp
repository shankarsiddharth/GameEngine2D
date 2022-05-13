#include "PhysicsSystem.h"
#include <vector>
#include "../Object/GameObject.h"
#include "../Component/RigidBody2D.h"
#include "../GameWorld.h"


PhysicsSystem::PhysicsSystem()
{

}

PhysicsSystem::~PhysicsSystem()
{

}

void PhysicsSystem::Initialize()
{

}

void PhysicsSystem::Update(float InDeltaTime, GameWorld* InGameWorld)
{
	std::vector<SharedPointer<GameObject>> gameObjects = InGameWorld->GetAllGameObjects();
	for (SharedPointer<GameObject> gameObject : gameObjects)
	{
		RigidBody2D* rigidBodyComponent = gameObject->GetComponent<RigidBody2D>();
		if (rigidBodyComponent != nullptr)
		{
			Vector2 netForce(Vector2::Zero);
			if (rigidBodyComponent->IsDragEnabled())
			{
				Vector2 currentVelocity = rigidBodyComponent->GetVelocity();
				rigidBodyComponent->SetDragForce(currentVelocity * -1.0f * rigidBodyComponent->GetDragCoefficient());
				netForce = rigidBodyComponent->GetDragForce() + rigidBodyComponent->GetForce();
			}
			else
			{
				netForce = rigidBodyComponent->GetForce();
			}

			//Calculate Dynamics - Euler MidPoint Method
			// a = F / m
			Vector2 accelaration = netForce / rigidBodyComponent->GetMass();
			Vector2 currentVelocity = rigidBodyComponent->GetVelocity();
			Vector2 previousVelocity = currentVelocity;

			//dv = a * dt
			Vector2 currentPosition = rigidBodyComponent->GetPosition();
			Vector2 newVelocity  = currentVelocity + accelaration * InDeltaTime;

			//dx = v * dt using Midpoint/Average
			Vector2 averageVelocity = (newVelocity + previousVelocity) / 2.0f;
			Vector2 newPosition = currentPosition + averageVelocity * InDeltaTime;

			rigidBodyComponent->SetPosition(newPosition);
			rigidBodyComponent->SetVelocity(newVelocity);

			// reset the net force
			//rigidBodyComponent->SetForce(Vector2::Zero);
		}
	}
}

void PhysicsSystem::ShutDown()
{

}
