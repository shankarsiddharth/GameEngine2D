#include "Sprite2D.h"
#include "../FileLoader/FileLoader.h"
#include "../../GLib/GLib.h"

Sprite2D::Sprite2D(const SharedPointer<GameObject>& InRootGameObject, std::string InFilePath)
	:Component(InRootGameObject),
	m_FilePath(InFilePath),
	m_GLibSprite(nullptr),
	m_Height(0),
	m_Width(0),
	m_Depth(0)
{
	m_GLibSprite = FileLoader::CreateSprite(m_FilePath.c_str(), m_Width, m_Height, m_Depth);
}

Sprite2D::~Sprite2D()
{
	GLib::Release(m_GLibSprite);
}

void Sprite2D::Start()
{
	//glibSprite = FileLoader::CreateSprite(filePath.c_str());
}

void Sprite2D::Update()
{

}

GLib::Sprite* Sprite2D::GetGLibSprite()
{
	return m_GLibSprite;
}

unsigned int Sprite2D::GetHeight() const
{
	return m_Height;
}

unsigned int Sprite2D::GetWidth() const
{
	return m_Width;
}

unsigned int Sprite2D::GetDepth() const
{
	return m_Depth;
}
