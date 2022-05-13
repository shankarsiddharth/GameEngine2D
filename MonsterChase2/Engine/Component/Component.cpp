#include "Component.h"

Component::Component(const SharedPointer<GameObject>& inRootGameObject)
	: rootGameObject(inRootGameObject)
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
	return rootGameObject;
}

