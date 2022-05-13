#pragma once
#include "../SmartPointer/SmartPointer.h"
#include "../Object/GameObject.h"

class GameObject;

class Component
{
public:
	Component(const SharedPointer<GameObject>& inRootGameObject);
	virtual ~Component();
	virtual void Start();
	virtual void Update();

	SharedPointer<GameObject> GetRootGameObject() const;

protected:
	SharedPointer<GameObject> rootGameObject;
};