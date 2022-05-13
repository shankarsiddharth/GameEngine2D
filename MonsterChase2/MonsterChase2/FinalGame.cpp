#include "FinalGame.h"
#include "GameRuntime.h"
#include "Object/GameObject.h"
#include "Component/Sprite2D.h"
#include "Component/RigidBody2D.h"
#include "JobSystem/JobSystem/JobSystem.h"
#include "Helpers/EngineHelpers.h"
#include "Component/BoxCollider2D.h"
#include "JobSystem/JobSystem/JobStatus.h"

FinalGame::FinalGame()
	:Game(), 
	m_Player(nullptr),
	m_Goal(nullptr)
{

}

FinalGame::~FinalGame()
{

}


void FinalGame::InitializeGameplay()
{
	gameWindow.SetWindowName("GameWindow");
	gameWindow.SetWindowHeight(800);
	gameWindow.SetWindowWidth(1200);
}

void FinalGame::StartGameplay()
{
	LoadGameObjects();
}

void FinalGame::ProcessInput()
{
	float force = 0.5f;

	if (inputSystem.IsKeyPressed(KeyCode::W))
	{
		m_Player->GetComponent<RigidBody2D>()->AddForce(Vector2(0, force));
	}
	if (inputSystem.IsKeyPressed(KeyCode::A))
	{
		m_Player->GetComponent<RigidBody2D>()->AddForce(Vector2(-force, 0));
	}
	if (inputSystem.IsKeyPressed(KeyCode::S))
	{
		m_Player->GetComponent<RigidBody2D>()->AddForce(Vector2(0, -force));
	}
	if (inputSystem.IsKeyPressed(KeyCode::D))
	{
		m_Player->GetComponent<RigidBody2D>()->AddForce(Vector2(force, 0));
	}

	//if (inputSystem.IsKeyPressed(KeyCode::Y))
	//{
	//	monster->GetComponent<RigidBody2D>()->AddForce(Vector2(0, force));
	//}
	//if (inputSystem.IsKeyPressed(KeyCode::G))
	//{
	//	monster->GetComponent<RigidBody2D>()->AddForce(Vector2(-force, 0));
	//}
	//if (inputSystem.IsKeyPressed(KeyCode::H))
	//{
	//	monster->GetComponent<RigidBody2D>()->AddForce(Vector2(0, -force));
	//}
	//if (inputSystem.IsKeyPressed(KeyCode::J))
	//{
	//	monster->GetComponent<RigidBody2D>()->AddForce(Vector2(force, 0));
	//}

	if (inputSystem.IsKeyPressed(KeyCode::K))
	{
		m_Player->AddRotationZ(0.01f);
	}
	if (inputSystem.IsKeyPressed(KeyCode::L))
	{
		m_Player->AddRotationZ(-0.01f);
	}


	if (inputSystem.IsKeyDown(KeyCode::O))
	{
		SharedPointer<GameObject> newGameObject = objectGenerator.CreateGameObjectFromJSONDocument(jsonParser.GetJSONDocument("data/player.json"));
		gameWorld.AddGameObject(newGameObject);
	}
	if (inputSystem.IsKeyDown(KeyCode::P))
	{
		gameWorld.RemoveGameObjectAtIndex(gameWorld.GetGameObjectsCount() - 1);
	}

}

void FinalGame::UpdateGameplay()
{
	/*gameTime += deltaTime;
	EngineHelpers::DebugPrint("DeltaTime: " + std::to_string(deltaTime));
	EngineHelpers::DebugPrint("GameTime: " + std::to_string(gameTime));
	if (gameTime >= 1000.0f)
	{
		if (monster)
		{
			gameWorld.RemoveGameObject(monster);
		}
		EngineHelpers::DebugPrint("30 seconds elapsed.");
		gameTime = 0.0f;
	}*/
}

void FinalGame::ShutDownGameplay()
{

}

void FinalGame::LoadGameObjects()
{
	std::string dataFilePath = "data/player.json";

	m_Player = CreateObject(dataFilePath);
	m_Player->GetComponent<BoxCollider2D>()->EnableCollisionCallback([this](SharedPointer<GameObject> CollidedObject) {
		EngineHelpers::DebugPrint(CollidedObject->GetName());
		RigidBody2D& rigidbody = *(this->m_Player->GetComponent<RigidBody2D>());
		Vector2 velocity = rigidbody.GetVelocity();
		Vector2 force = rigidbody.GetForce();
		//rigidbody.AddForce(force * -2.0f);
		//rigidbody.SetVelocity(Vector2::Zero);
		//rigidbody.SetForce(Vector2::Zero);
		this->direction = this->direction * -1.0f;
		});

	dataFilePath = "data/goal.json";
	m_Goal = CreateObject(dataFilePath);

	dataFilePath = "data/obstacle.json";
	SharedPointer<GameObject> newObstacle = CreateObject(dataFilePath);
	m_ObstaclesList.push_back(newObstacle);
}
