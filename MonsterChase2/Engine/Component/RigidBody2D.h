#pragma once
#include "Component.h"
#include "../Math/Vector2.h"

class RigidBody2D
	:public Component
{
public:
	RigidBody2D(GameObject* i_RootGameObject, 
		float i_Mass = 1.0f, 
		float i_CoefficientDrag = 0.0f,  
		bool i_EnableDrag = false,
		bool i_EnableGravity = false);
	~RigidBody2D();

	void Start() override;
	void Update() override;

	void AddForce(Vector2 i_Force);
	void SetForce(Vector2 i_Force);
	Vector2 GetForce();

	Vector2 GetVelocity() const;
	void SetVelocity(Vector2 i_Veclocity);

	Vector2 GetPosition() const;
	void SetPosition(Vector2 i_Position);

	float GetMass() const;

protected:
	Vector2 m_Velocity;
	Vector2 m_Force;
	float m_Mass;
};
