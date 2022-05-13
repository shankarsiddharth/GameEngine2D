#include "RigidBody2D.h"
#include "../Object/GameObject.h"

RigidBody2D::RigidBody2D(const SharedPointer<GameObject>& InRootGameObject, float InMass /*= 1.0f*/,
	float InCoefficientDrag /*= 0.0f*/, bool InEnableDrag /*= true*/,
	bool InEnableGravity /*= false*/)
	:Component(InRootGameObject),
	m_Velocity(Vector2::Zero),
	m_Force(Vector2::Zero),
	m_Mass(InMass),
	m_IsDragEnabled(InEnableDrag),
	m_CoefficientDrag(InCoefficientDrag)
{

}

RigidBody2D::~RigidBody2D()
{

}

void RigidBody2D::Start()
{

}

void RigidBody2D::Update()
{

}

void RigidBody2D::AddForce(Vector2 InForce)
{
	//TODO: Change to add force
	m_Force = InForce;

	//m_Force += i_Force;
}

void RigidBody2D::SetForce(Vector2 InForce)
{
	m_Force = InForce;
}

Vector2 RigidBody2D::GetForce()
{
	return m_Force;
}

Vector2 RigidBody2D::GetVelocity() const
{
	return m_Velocity;
}

void RigidBody2D::SetVelocity(Vector2 InVeclocity)
{
	m_Velocity = InVeclocity;
}

Vector2 RigidBody2D::GetPosition() const
{
	return m_RootGameObject->GetPosition();
}

void RigidBody2D::SetPosition(Vector2 InPosition)
{
	m_RootGameObject->SetPosition(InPosition);
}

float RigidBody2D::GetMass() const
{
	return m_Mass;
}

bool RigidBody2D::IsDragEnabled() const
{
	return m_IsDragEnabled;
}

float RigidBody2D::GetDragCoefficient() const
{
	return m_CoefficientDrag;
}

Vector2 RigidBody2D::GetDragForce() const
{
	return m_Drag;
}

void RigidBody2D::SetDragForce(Vector2 InDragForce)
{
	m_Drag = InDragForce;
}

