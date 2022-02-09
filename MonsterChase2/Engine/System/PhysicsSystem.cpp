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

void PhysicsSystem::Update(float deltaTime, GameWorld* i_GameWorld)
{
	std::vector<GameObject*> gameObjects = i_GameWorld->GetAllGameObjects();
	for (GameObject* gameObject : gameObjects)
	{		
		RigidBody2D* rigidBodyComponent = gameObject->GetComponent<RigidBody2D>();
		if (rigidBodyComponent != nullptr)
		{
			//Calculate Dynamics - Euler MidPoint Method
			// a = F / m
			Vector2 accelaration = rigidBodyComponent->GetForce() / rigidBodyComponent->GetMass();
			Vector2 currentVelocity = rigidBodyComponent->GetVelocity();
			Vector2 previousVelocity = currentVelocity;

			//dv = a * dt
			Vector2 currentPosition = rigidBodyComponent->GetPosition();
			currentVelocity += accelaration * deltaTime;

			//dx = v * dt using Midpoint/Average
			Vector2 averageVelocity = (currentVelocity + previousVelocity) / 2.0f;
			currentPosition += averageVelocity * deltaTime;

			rigidBodyComponent->SetPosition(currentPosition);
			rigidBodyComponent->SetVelocity(currentVelocity);

			// reset the net force
			rigidBodyComponent->SetForce(Vector2::Zero); 
		}
	}
}

void PhysicsSystem::ShutDown()
{

}
