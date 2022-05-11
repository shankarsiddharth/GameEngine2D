#pragma once
#include "Component.h"
#include <vector>
#include "../Math/Vector4.h"

class BoxCollider2D
	:public Component
{
public:
	BoxCollider2D(const SharedPointer<GameObject>& i_RootGameObject);
	~BoxCollider2D();

	void Start() override;
	void Update() override;

protected:
	//Index 0 - TopLeft, 1- TopRight, 2- BottomLeft, 3-BottomRight
	std::vector<Vector4> localExtentCoordinates;
	std::vector<Vector4> worldExtentCoordinates;
};
