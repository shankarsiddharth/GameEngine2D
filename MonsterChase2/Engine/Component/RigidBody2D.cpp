#include "RigidBody2D.h"
#include "../Object/GameObject.h"

RigidBody2D::RigidBody2D(const SharedPointer<GameObject>& i_RootGameObject, float i_Mass /*= 1.0f*/,
	float i_CoefficientDrag /*= 0.0f*/, bool i_EnableDrag /*= true*/,
	bool i_EnableGravity /*= false*/)
	:Component(i_RootGameObject),
	m_Velocity(Vector2::Zero),
	m_Force(Vector2::Zero),
	m_Mass(i_Mass),
	m_isDragEnabled(i_EnableDrag),
	m_CoefficientDrag(i_CoefficientDrag)
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

void RigidBody2D::AddForce(Vector2 i_Force)
{
	//TODO: Change to add force
	m_Force = i_Force;
}

void RigidBody2D::SetForce(Vector2 i_Force)
{
	m_Force = i_Force;
}

Vector2 RigidBody2D::GetForce()
{
	return m_Force;
}

Vector2 RigidBody2D::GetVelocity() const
{
	return m_Velocity;
}

void RigidBody2D::SetVelocity(Vector2 i_Veclocity)
{
	m_Velocity = i_Veclocity;
}

Vector2 RigidBody2D::GetPosition() const
{
	return rootGameObject->GetPosition();
}

void RigidBody2D::SetPosition(Vector2 i_Position)
{
	rootGameObject->SetPosition(i_Position);
}

float RigidBody2D::GetMass() const
{
	return m_Mass;
}

bool RigidBody2D::IsDragEnabled() const
{
	return m_isDragEnabled;
}

float RigidBody2D::GetDragCoefficient() const
{
	return m_CoefficientDrag;
}

Vector2 RigidBody2D::GetDragForce() const
{
	return m_Drag;
}

void RigidBody2D::SetDragForce(Vector2 val)
{
	m_Drag = val;
}

