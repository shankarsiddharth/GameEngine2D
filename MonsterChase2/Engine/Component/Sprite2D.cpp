#include "Sprite2D.h"
#include "../FileLoader/FileLoader.h"
#include "../../GLib/GLib.h"

Sprite2D::Sprite2D(const SharedPointer<GameObject>& i_RootGameObject, std::string i_filePath)
	:Component(i_RootGameObject),
	filePath(i_filePath),
	glibSprite(nullptr)
{
	glibSprite = FileLoader::CreateSprite(filePath.c_str());
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
