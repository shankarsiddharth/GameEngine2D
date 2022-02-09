#pragma once

class GameObject;

class Component
{
public:
	Component(GameObject* inRootGameObject);
	virtual ~Component();
	virtual void Start();
	virtual void Update();
protected:
	GameObject* rootGameObject;
};