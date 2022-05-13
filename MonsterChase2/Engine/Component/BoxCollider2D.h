#pragma once
#include "Component.h"
#include <vector>
#include "../Math/Vector4.h"
#include <functional>

class CollisionSystem;

typedef std::function<void(SharedPointer<GameObject>)> FCollisionCallback;

class BoxCollider2D
	:public Component
{
	friend class CollisionSystem;

public:
	BoxCollider2D(const SharedPointer<GameObject>& i_RootGameObject);
	~BoxCollider2D();

	void Start() override;
	void Update() override;

	void UpdateWorldExtents();
	void UpdateWorldExtentsAxes();

	std::vector<Vector4> GetWorldExtentAxes() const;
	std::vector<Vector4> GetWorldExtentCoordinates() const;

	void EnableCollisionCallback(FCollisionCallback i_CollisionCallback);

protected:

	void UpdateWorldExtentsEdges();
	void ExecuteCollisionCallback(SharedPointer<GameObject> CollidedGameObject);

	//Index 0 - TopLeft, 1- TopRight, 3-BottomRight , 4-BottomLeft
	std::vector<Vector4> localExtentCoordinates;
	std::vector<Vector4> worldExtentCoordinates;

	std::vector<Vector4> worldExtentEdges;
	std::vector<Vector4> worldExtentAxes;

	FCollisionCallback OnCollision;

};
