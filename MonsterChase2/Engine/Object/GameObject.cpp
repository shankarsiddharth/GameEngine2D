#include "GameObject.h"
#include "../Component/Component.h"
#include "../Helpers/EngineHelpers.h"

GameObject::GameObject()
	:m_Position(Vector2(0,0)),
	m_Visibility(true)
{
}

GameObject::~GameObject()
{
	if (m_ComponentList.size() != 0)
	{
		RemoveAllComponents();
	}
	EngineHelpers::DebugPrint(m_Name + " deleted.");
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

void GameObject::AddRotationZ(float InValue)
{
	m_Rotation.Z(m_Rotation.Z() + InValue);
}

std::vector<Component*> GameObject::GetAllComponents()
{
	return m_ComponentList;
}

void GameObject::RemoveAllComponents()
{
	for (Component* element: m_ComponentList)
	{
		if (element != nullptr)
		{
			delete element;
			element = nullptr;
		}
	}
	m_ComponentList.clear();
}

std::string GameObject::GetName() const
{
	return m_Name;
}

void GameObject::SetName(std::string InName)
{
	m_Name = InName;
}

bool GameObject::IsVisible() const
{
	return m_Visibility;
}

void GameObject::SetVisibility(bool InVisibility)
{
	m_Visibility = InVisibility;
}
