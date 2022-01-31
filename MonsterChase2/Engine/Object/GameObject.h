#pragma once
#include "../Math/Point2D.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	Point2D GetPosition() const;

	void Move(const Point2D& InMoveBy);	

	void SetPosition(const Point2D& InNewPosition);
	
protected:
	Point2D m_Position;
};

