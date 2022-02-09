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
	Sprite2D(GameObject* i_RootGameObject, std::string i_filePath);
	~Sprite2D();

	void Start() override;
	void Update() override;

protected:
	std::string filePath;
	GLib::Sprite* glibSprite;
};

