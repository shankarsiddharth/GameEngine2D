#include "GameObject.h"

GameObject::GameObject()
	:m_Position(Point2D(0,0))
{
}

GameObject::~GameObject()
{
	
};

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
