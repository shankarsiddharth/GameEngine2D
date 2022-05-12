#pragma once
#include "../Math/Vector2.h"
#include <vector>
#include "../Math/Vector4.h"

class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

	Vector2 GetPosition() const;	
	void SetPosition(const Vector2& InNewPosition);
	void Move(const Vector2& InMoveBy);

	Vector4 GetRotation() const;
	void SetRotation(const Vector4& InNewRotation);
	void AddRotationZ(float InValue);

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
	Vector4 m_Rotation;
	std::vector<Component*> componentList;
};

#include "GameObject_inl.h"
