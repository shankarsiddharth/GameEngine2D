#pragma once
#include "Component.h"
#include "../Math/Vector2.h"

class RigidBody2D
	:public Component
{
public:
	RigidBody2D(const SharedPointer<GameObject>& InRootGameObject,
		float InMass = 1.0f, 
		float InCoefficientDrag = 0.0f,  
		bool InEnableDrag = true,
		bool InEnableGravity = false);
	~RigidBody2D();

	void Start() override;
	void Update() override;

	void AddForce(Vector2 InForce);
	void SetForce(Vector2 InForce);
	Vector2 GetForce();

	Vector2 GetVelocity() const;
	void SetVelocity(Vector2 InVeclocity);

	Vector2 GetPosition() const;
	void SetPosition(Vector2 InPosition);

	float GetMass() const;

	bool IsDragEnabled() const;
	float GetDragCoefficient() const;

	Vector2 GetDragForce() const;
	void SetDragForce(Vector2 InDragForce);

protected:
	Vector2 m_Velocity;
	Vector2 m_Force;
	float m_Mass;

	bool m_IsDragEnabled;
	Vector2 m_Drag;
	float m_CoefficientDrag;
};
