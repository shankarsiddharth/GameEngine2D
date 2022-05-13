#pragma once
#include "Component.h"
#include <string>

namespace GLib
{
	class Sprite;
}

class Sprite2D :
	public Component
{
public:
	Sprite2D(const SharedPointer<GameObject>& InRootGameObject, std::string InFilePath);
	~Sprite2D();

	void Start() override;
	void Update() override;

	GLib::Sprite* GetGLibSprite();

	unsigned int GetHeight() const;
	unsigned int GetWidth() const;
	unsigned int GetDepth() const;

protected:
	std::string m_FilePath;
	GLib::Sprite* m_GLibSprite;

	unsigned int m_Height;
	unsigned int m_Width;
	unsigned int m_Depth;
};

