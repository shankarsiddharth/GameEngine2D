#include "Sprite2D.h"
#include "../FileLoader/FileLoader.h"
#include "../../GLib/GLib.h"

Sprite2D::Sprite2D(const SharedPointer<GameObject>& i_RootGameObject, std::string i_filePath)
	:Component(i_RootGameObject),
	filePath(i_filePath),
	glibSprite(nullptr),
	height(0),
	width(0),
	depth(0)
{
	glibSprite = FileLoader::CreateSprite(filePath.c_str(), width, height, depth);
}

Sprite2D::~Sprite2D()
{
	GLib::Release(glibSprite);
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
	return glibSprite;
}

unsigned int Sprite2D::GetHeight() const
{
	return height;
}

unsigned int Sprite2D::GetWidth() const
{
	return width;
}

unsigned int Sprite2D::GetDepth() const
{
	return depth;
}
