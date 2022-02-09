#pragma once
#include "../Math/Vector2.h"
#include <vector>

class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

	Vector2 GetPosition() const;
	void Move(const Vector2& InMoveBy);
	void SetPosition(const Vector2& InNewPosition);


	template<class T>
	void AddComponent(T* newComponent);
	template<class T>
	T* GetComponent();
	template<class T>
	void RemoveComponent();
	template<class T>
	bool HasComponent();

	std::vector<Component*> GetAllComponents();
	void RemoveAllComponents();


protected:
	Vector2 m_Position;
	std::vector<Component*> componentList;
};

#include "GameObject_inl.h"
