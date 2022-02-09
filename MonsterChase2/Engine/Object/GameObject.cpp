#include "GameObject.h"
#include "../Component/Component.h"

GameObject::GameObject()
	:m_Position(Point2D(0,0))
{
}

GameObject::~GameObject()
{
	if (componentList.size() != 0)
	{
		RemoveAllComponents();
	}
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

std::vector<Component*> GameObject::GetAllComponents()
{
	return componentList;
}

void GameObject::RemoveAllComponents()
{
	for (Component* element: componentList)
	{
		if (element != nullptr)
		{
			delete element;
			element = nullptr;
		}
	}
	componentList.clear();
}
