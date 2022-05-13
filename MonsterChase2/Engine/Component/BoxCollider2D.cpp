#include "BoxCollider2D.h"
#include "Sprite2D.h"
#include "../Object/GameObject.h"
#include "../Math/Matrix4x4.h"

BoxCollider2D::BoxCollider2D(const SharedPointer<GameObject>& InRootGameObject)
	:Component(InRootGameObject)
{
	int spriteHeight = 0;
	int spriteWidth = 0;
	int spriteDepth = 0;

	if (m_RootGameObject->HasComponent<Sprite2D>())
	{
		const Sprite2D& sprite2d = *(m_RootGameObject->GetComponent<Sprite2D>());
		spriteHeight = sprite2d.GetHeight();
		spriteWidth = sprite2d.GetWidth();
		spriteDepth = sprite2d.GetDepth();
	}

	Vector2 localTopLeftExtent(-1.0f * (float)(spriteWidth / 2), (float)spriteHeight);
	Vector2 localTopRightExtent((float)(spriteWidth / 2), (float)spriteHeight);
	Vector2 localBottomLeftExtent(-1.0f * (float)(spriteWidth / 2), 0);
	Vector2 localBottomRightExtent((float)(spriteWidth / 2), 0);

	m_LocalExtentCoordinates.push_back(Vector4(localTopLeftExtent, 0.0f, 1.0f));
	m_LocalExtentCoordinates.push_back(Vector4(localTopRightExtent, 0.0f, 1.0f));
	m_LocalExtentCoordinates.push_back(Vector4(localBottomRightExtent, 0.0f, 1.0f));
	m_LocalExtentCoordinates.push_back(Vector4(localBottomLeftExtent, 0.0f, 1.0f));
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
	m_WorldExtentCoordinates.clear();

	Vector2 gameObjectPosition = m_RootGameObject->GetPosition();
	Vector4 gameObjectRotation = m_RootGameObject->GetRotation();

	Matrix4x4 translationMatrix = Matrix4x4::TranslationMatrix(gameObjectPosition.X(), gameObjectPosition.Y(), 0.0f);
	Matrix4x4 rotationMatrix = Matrix4x4::ZRotationMatrix(gameObjectRotation.Z());

	Matrix4x4 localToWorldMartrix = translationMatrix * rotationMatrix;

	for (size_t i = 0; i < m_LocalExtentCoordinates.size(); i++)
	{
		Vector4 worldExtent = localToWorldMartrix * m_LocalExtentCoordinates[i];
		m_WorldExtentCoordinates.push_back(worldExtent);
	}
}

void BoxCollider2D::UpdateWorldExtentsAxes()
{
	m_WorldExtentEdges.clear();
	m_WorldExtentAxes.clear();

	for (size_t i = 0; i < m_WorldExtentCoordinates.size(); i++)
	{
		Vector4 currentvertex = m_WorldExtentCoordinates[i];

		const size_t nextIndex = (i + 1) % m_WorldExtentCoordinates.size();
		Vector4 nextVertex = m_WorldExtentCoordinates[nextIndex];

		Vector4 worldExtentEdge = nextVertex - currentvertex;

		m_WorldExtentEdges.push_back(worldExtentEdge);

		Vector2 edgeXY(worldExtentEdge.X(), worldExtentEdge.Y());
		Vector2 normalizedEdgeXY = edgeXY.GetNormalVector();
		Vector2 edgeAxis = Vector2::PerpendicularVector(normalizedEdgeXY);
		Vector4 worldExtentAxis(edgeAxis, 0.0f, 1.0f);

		m_WorldExtentAxes.push_back(worldExtentAxis);
	}
}

std::vector<Vector4> BoxCollider2D::GetWorldExtentAxes() const
{
	return m_WorldExtentAxes;
}

std::vector<Vector4> BoxCollider2D::GetWorldExtentCoordinates() const
{
	return m_WorldExtentCoordinates;
}

void BoxCollider2D::EnableCollisionCallback(FCollisionCallback InCollisionCallback)
{
	m_OnCollision = InCollisionCallback;
}

void BoxCollider2D::ExecuteCollisionCallback(SharedPointer<GameObject> InCollidedGameObject)
{
	if (m_OnCollision)
	{
		m_OnCollision(InCollidedGameObject);
	}
}

void BoxCollider2D::UpdateWorldExtentsEdges()
{
	m_WorldExtentEdges.clear();
	m_WorldExtentAxes.clear();

	Vector4 worldExtentEdge1 = m_WorldExtentCoordinates[1] - m_WorldExtentCoordinates[0];
	Vector4 worldExtentEdge2 = m_WorldExtentCoordinates[2] - m_WorldExtentCoordinates[1];
	Vector4 worldExtentEdge3 = m_WorldExtentCoordinates[3] - m_WorldExtentCoordinates[2];
	Vector4 worldExtentEdge4 = m_WorldExtentCoordinates[0] - m_WorldExtentCoordinates[3];

	m_WorldExtentEdges.push_back(worldExtentEdge1);
	m_WorldExtentEdges.push_back(worldExtentEdge2);
	m_WorldExtentEdges.push_back(worldExtentEdge3);
	m_WorldExtentEdges.push_back(worldExtentEdge4);

	for (size_t index = 0; index < m_WorldExtentEdges.size(); index++)
	{
		Vector2 edgeXY(m_WorldExtentEdges[index].X(), m_WorldExtentEdges[index].Y());
		Vector2 normalizedEdgeXY = edgeXY.GetNormalVector();
		Vector2 edgeAxis = Vector2::PerpendicularVector(normalizedEdgeXY);
		Vector4 worldExtentAxis(edgeAxis, 0.0f, 1.0f);

		m_WorldExtentAxes.push_back(worldExtentAxis);
	}
}

//std::vector<Vector4> BoxCollider2D::GetWorldExtentEdges() const
//{
//	return worldExtentEdges;
//}

