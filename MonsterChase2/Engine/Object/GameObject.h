#pragma once
#include "../Math/Point2D.h"
#include "../String/String.h"

class GameObject
{
public:
	GameObject();
	GameObject(char* InName);
	~GameObject();

	String* GetName() const;
	Point2D GetPosition() const;

	void Move(const Point2D& InMoveBy);	

	void SetPosition(const Point2D& InNewPosition);
	void SetName(const char* InName);
	
protected:
	String* m_Name;
	Point2D m_Position;
};

