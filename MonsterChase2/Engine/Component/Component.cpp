#include "Component.h"

Component::Component(const SharedPointer<GameObject>& InRootGameObject)
	: m_RootGameObject(InRootGameObject)
{

}

Component::~Component()
{

}

void Component::Start()
{

}

void Component::Update()
{

}

SharedPointer<GameObject> Component::GetRootGameObject() const
{
	return m_RootGameObject;
}

