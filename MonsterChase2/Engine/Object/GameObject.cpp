#include "GameObject.h"

GameObject::GameObject()
	:m_Position(Point2D(0,0))
{	
	m_Name = new String();
}

GameObject::GameObject(char* InName)
	: m_Position(Point2D(0, 0))
{
	m_Name = new String();
	m_Name->CopyString(InName);
}

GameObject::~GameObject()
{
	if (m_Name)
	{
		delete m_Name;
		m_Name = nullptr;
	}
}

String* GameObject::GetName() const
{
	return m_Name;
}

Point2D GameObject::GetPosition() const
{
	return m_Position;
}

void GameObject::Move(const Point2D& InMoveBy)
{
	m_Position += InMoveBy;
}

void GameObject::SetPosition(const Point2D& InNewPosition)
{
	m_Position = InNewPosition;
}

void GameObject::SetName(const char* InName)
{
	m_Name->CopyString(InName);
}
