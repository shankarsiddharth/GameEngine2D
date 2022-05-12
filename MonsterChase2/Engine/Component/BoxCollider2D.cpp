#include "BoxCollider2D.h"
#include "Sprite2D.h"
#include "../Object/GameObject.h"
#include "../Math/Matrix4x4.h"

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

	Vector2 localTopLeftExtent(-1.0f * (float)(spriteWidth / 2), (float)spriteHeight);
	Vector2 localTopRightExtent((float)(spriteWidth / 2), (float)spriteHeight);
	Vector2 localBottomLeftExtent(-1.0f * (float)(spriteWidth / 2), 0);
	Vector2 localBottomRightExtent((float)(spriteWidth / 2), 0);

	localExtentCoordinates.push_back(Vector4(localTopLeftExtent, 0.0f, 1.0f));
	localExtentCoordinates.push_back(Vector4(localTopRightExtent, 0.0f, 1.0f));
	localExtentCoordinates.push_back(Vector4(localBottomRightExtent, 0.0f, 1.0f));
	localExtentCoordinates.push_back(Vector4(localBottomLeftExtent, 0.0f, 1.0f));
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

void BoxCollider2D::UpdateWorldExtents()
{
	worldExtentCoordinates.clear();

	Vector2 gameObjectPosition = rootGameObject->GetPosition();
	Vector4 gameObjectRotation = rootGameObject->GetRotation();

	//TODO: Check the ZValue passed to create the translation matrix
	Matrix4x4 translationMatrix = Matrix4x4::TranslationMatrix(gameObjectPosition.X(), gameObjectPosition.Y(), 0.0f);
	Matrix4x4 rotationMatrix = Matrix4x4::ZRotationMatrix(gameObjectRotation.Z());

	Matrix4x4 localToWorldMartrix = translationMatrix * rotationMatrix;

	for (size_t i = 0; i < localExtentCoordinates.size(); i++)
	{
		Vector4 worldExtent = localToWorldMartrix * localExtentCoordinates[i];
		worldExtentCoordinates.push_back(worldExtent);
	}
}

void BoxCollider2D::UpdateWorldExtentsAxes()
{
	worldExtentEdges.clear();
	worldExtentAxes.clear();

	for (size_t i = 0; i < worldExtentCoordinates.size(); i++)
	{
		Vector4 currentvertex = worldExtentCoordinates[i];

		const size_t nextIndex = (i + 1) % worldExtentCoordinates.size();
		Vector4 nextVertex = worldExtentCoordinates[nextIndex];

		Vector4 worldExtentEdge = nextVertex - currentvertex;

		worldExtentEdges.push_back(worldExtentEdge);

		Vector2 edgeXY(worldExtentEdge.X(), worldExtentEdge.Y());
		Vector2 normalizedEdgeXY = edgeXY.GetNormalVector();
		Vector2 edgeAxis = Vector2::PerpendicularVector(normalizedEdgeXY);
		Vector4 worldExtentAxis(edgeAxis, 0.0f, 1.0f);

		worldExtentAxes.push_back(worldExtentAxis);
	}
}

std::vector<Vector4> BoxCollider2D::GetWorldExtentAxes() const
{
	return worldExtentAxes;
}

std::vector<Vector4> BoxCollider2D::GetWorldExtentCoordinates() const
{
	return worldExtentCoordinates;
}

void BoxCollider2D::UpdateWorldExtentsEdges()
{
	worldExtentEdges.clear();
	worldExtentAxes.clear();

	Vector4 worldExtentEdge1 = worldExtentCoordinates[1] - worldExtentCoordinates[0];
	Vector4 worldExtentEdge2 = worldExtentCoordinates[2] - worldExtentCoordinates[1];
	Vector4 worldExtentEdge3 = worldExtentCoordinates[3] - worldExtentCoordinates[2];
	Vector4 worldExtentEdge4 = worldExtentCoordinates[0] - worldExtentCoordinates[3];

	worldExtentEdges.push_back(worldExtentEdge1);
	worldExtentEdges.push_back(worldExtentEdge2);
	worldExtentEdges.push_back(worldExtentEdge3);
	worldExtentEdges.push_back(worldExtentEdge4);

	for (size_t index = 0; index < worldExtentEdges.size(); index++)
	{
		Vector2 edgeXY(worldExtentEdges[index].X(), worldExtentEdges[index].Y());
		Vector2 normalizedEdgeXY = edgeXY.GetNormalVector();
		Vector2 edgeAxis = Vector2::PerpendicularVector(normalizedEdgeXY);
		Vector4 worldExtentAxis(edgeAxis, 0.0f, 1.0f);

		worldExtentAxes.push_back(worldExtentAxis);
	}
}

//std::vector<Vector4> BoxCollider2D::GetWorldExtentEdges() const
//{
//	return worldExtentEdges;
//}

