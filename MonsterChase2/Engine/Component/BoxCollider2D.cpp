#include "BoxCollider2D.h"
#include "Sprite2D.h"
#include "../Object/GameObject.h"

BoxCollider2D::BoxCollider2D(const SharedPointer<GameObject>& i_RootGameObject)
	:Component(i_RootGameObject)
{
	int spriteHeight = 0; 
	int spriteWidth = 0;
	int spriteDepth = 0;

	if (rootGameObject->HasComponent<Sprite2D>())
	{
		const Sprite2D& sprite2d = *(rootGameObject->GetComponent<Sprite2D>());
		spriteHeight = sprite2d.GetHeight();
		spriteWidth = sprite2d.GetWidth();
		spriteDepth = sprite2d.GetDepth();
	}

	Vector2 localTopLeftExtent(-1.0f * (float)(spriteWidth/2), (float)spriteHeight);
	Vector2 localTopRightExtent((float)(spriteWidth/2), (float)spriteHeight);
	Vector2 localBottomLeftExtent(-1.0f * (float)(spriteWidth/2), 0);
	Vector2 localBottomRightExtent((float)(spriteWidth/2), 0);


	localExtentCoordinates.push_back(Vector4(localTopLeftExtent, 1.0f, 1.0f));
	localExtentCoordinates.push_back(Vector4(localTopRightExtent, 1.0f, 1.0f));
	localExtentCoordinates.push_back(Vector4(localBottomLeftExtent, 1.0f, 1.0f));
	localExtentCoordinates.push_back(Vector4(localBottomRightExtent, 1.0f, 1.0f));
}

BoxCollider2D::~BoxCollider2D()
{

}

void BoxCollider2D::Start()
{
	
}

void BoxCollider2D::Update()
{
	
}

