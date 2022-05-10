#include "ObjectGenerator.h"

ObjectGenerator::ObjectGenerator()
{

}

ObjectGenerator::~ObjectGenerator()
{

}

GameObject* ObjectGenerator::CreateGameObjectFromJSONDocument(const rapidjson::Document i_JSONDocument)
{
	if (i_JSONDocument.IsObject())
	{
		return new GameObject();
	}
	return nullptr;
}
