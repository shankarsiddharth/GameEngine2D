#pragma once

#include "GameObject.h"
#include "../ThirdParty/rapidjson/document.h"

class ObjectGenerator
{
public:
	ObjectGenerator();
	~ObjectGenerator();
	GameObject* CreateGameObjectFromJSONDocument(const rapidjson::Document i_JSONDocument);

};