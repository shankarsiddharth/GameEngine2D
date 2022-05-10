#include "ObjectGenerator.h"
#include "../SmartPointer/SmartPointer.h"
#include <stddef.h>

ObjectGenerator::ObjectGenerator()
{

}

ObjectGenerator::~ObjectGenerator()
{

}

SharedPointer<GameObject> ObjectGenerator::CreateGameObjectFromJSONDocument(const rapidjson::Document i_JSONDocument)
{
	if (!i_JSONDocument.IsObject())
	{
		return SharedPointer<GameObject>(nullptr);
	}

	SharedPointer<GameObject> newGameObject(new GameObject());

	//Read JSON File and Create components
	
	return newGameObject;
}
