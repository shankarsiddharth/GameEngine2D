#pragma once
#include "Component.h"
#include "../Math/Vector2.h"

class BoxCollider2D
	:public Component
{
public:
	BoxCollider2D(const SharedPointer<GameObject>& i_RootGameObject);
	~BoxCollider2D();

	void Start() override;
	void Update() override;

protected:

};
