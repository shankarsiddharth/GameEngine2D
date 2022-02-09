#pragma once
#include "../Math/Point2D.h"
#include <vector>

class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

	Point2D GetPosition() const;
	void Move(const Point2D& InMoveBy);
	void SetPosition(const Point2D& InNewPosition);


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
	Point2D m_Position;
	std::vector<Component*> componentList;
};

#include "GameObject_inl.h"
