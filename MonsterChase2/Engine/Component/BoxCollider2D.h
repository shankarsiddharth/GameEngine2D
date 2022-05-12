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

	void UpdateWorldExtents();
	void UpdateWorldExtentsAxes();

	std::vector<Vector4> GetWorldExtentAxes() const;
	std::vector<Vector4> GetWorldExtentCoordinates() const;

protected:

	void UpdateWorldExtentsEdges();

	//Index 0 - TopLeft, 1- TopRight, 2- BottomLeft, 3-BottomRight
	std::vector<Vector4> localExtentCoordinates;
	std::vector<Vector4> worldExtentCoordinates;

	std::vector<Vector4> worldExtentEdges;
	std::vector<Vector4> worldExtentAxes;
};
