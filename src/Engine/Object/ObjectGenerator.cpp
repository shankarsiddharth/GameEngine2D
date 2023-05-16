#include "ObjectGenerator.h"
#include "../SmartPointer/SmartPointer.h"
#include <stddef.h>
#include <string>
#include "../Component/Sprite2D.h"
#include "../Component/RigidBody2D.h"
#include "../Component/BoxCollider2D.h"

ObjectGenerator::ObjectGenerator()
{

}

ObjectGenerator::~ObjectGenerator()
{

}

SharedPointer<GameObject> ObjectGenerator::CreateGameObjectFromJSONDocument(const rapidjson::Document InJSONDocument)
{
	if (!InJSONDocument.IsObject())
	{
		return SharedPointer<GameObject>(nullptr);
	}

	SharedPointer<GameObject> newGameObject(new GameObject());

	//Read JSON File and Create components
	if (InJSONDocument.HasMember("position"))
	{
		const rapidjson::Value& positionValue = InJSONDocument["position"];
		float x = positionValue[0].GetFloat();
		float y = positionValue[1].GetFloat();
		newGameObject->SetPosition(Vector2(x, y));
	}

	if (InJSONDocument.HasMember("name"))
	{
		const rapidjson::Value& nameValue = InJSONDocument["name"];
		std::string gameObjectName = nameValue.GetString();
		newGameObject->SetName(gameObjectName);
	}

	if (InJSONDocument.HasMember("components"))
	{
		const rapidjson::Value& componentsValue = InJSONDocument["components"];

		if (componentsValue.HasMember("sprite2d"))
		{
			const rapidjson::Value& sprite2dValue = componentsValue["sprite2d"];
			std::string sprite2dFilePath = sprite2dValue["filepath"].GetString();
			newGameObject->AddComponent(new Sprite2D(newGameObject, sprite2dFilePath));
		}

		if (componentsValue.HasMember("rigidbody2d"))
		{
			const rapidjson::Value& rigidBodyValue = componentsValue["rigidbody2d"];
			float rigidbody2dMass = rigidBodyValue["mass"].GetFloat();
			float dragcoefficient = 0.0f;
			if (rigidBodyValue.HasMember("dragcoefficient"))
			{
				dragcoefficient = rigidBodyValue["dragcoefficient"].GetFloat();
			}
			newGameObject->AddComponent(new RigidBody2D(newGameObject, rigidbody2dMass, dragcoefficient));
		}

		if (componentsValue.HasMember("boxcollider2d"))
		{
			const rapidjson::Value& rigidBodyValue = componentsValue["boxcollider2d"];			
			newGameObject->AddComponent(new BoxCollider2D(newGameObject));
		}
	}
	
	return newGameObject;
}
