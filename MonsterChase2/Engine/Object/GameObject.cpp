#include "GameObject.h"
#include "../Component/Component.h"

GameObject::GameObject()
	:m_Position(Vector2(0,0))
{
}

GameObject::~GameObject()
{
	if (componentList.size() != 0)
	{
		RemoveAllComponents();
	}
};

Vector2 GameObject::GetPosition() const
{
	return m_Position;
}

void GameObject::Move(const Vector2& InMoveBy)
{
	m_Position += InMoveBy;
}

void GameObject::SetPosition(const Vector2& InNewPosition)
{
	m_Position = InNewPosition;
}

Vector4 GameObject::GetRotation() const
{
	return m_Rotation;
}

void GameObject::SetRotation(const Vector4& InNewRotation)
{
	m_Rotation = InNewRotation;
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
