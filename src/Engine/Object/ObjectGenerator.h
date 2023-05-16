#pragma once

#include "GameObject.h"
#include "../ThirdParty/rapidjson/document.h"
#include "../SmartPointer/SmartPointer.h"

class ObjectGenerator
{
public:
	ObjectGenerator();
	~ObjectGenerator();
	SharedPointer<GameObject> CreateGameObjectFromJSONDocument(const rapidjson::Document InJSONDocument);

};