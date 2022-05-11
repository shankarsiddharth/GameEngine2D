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
	Sprite2D(const SharedPointer<GameObject>& i_RootGameObject, std::string i_filePath);
	~Sprite2D();

	void Start() override;
	void Update() override;

	GLib::Sprite* GetGLibSprite();

	unsigned int GetHeight() const;
	unsigned int GetWidth() const;
	unsigned int GetDepth() const;

protected:
	std::string filePath;
	GLib::Sprite* glibSprite;

	unsigned int height;
	unsigned int width;
	unsigned int depth;
};

