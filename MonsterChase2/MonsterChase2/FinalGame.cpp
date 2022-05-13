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
	m_Goal(nullptr),
	m_CurrentGameState(TGameState::kStart)
{

}

FinalGame::~FinalGame()
{

}

void FinalGame::InitializeGameplay()
{
	m_GameWindow.SetWindowName("GameWindow");
	m_GameWindow.SetWindowHeight(800);
	m_GameWindow.SetWindowWidth(1200);

	ListenForCollisions(std::bind(&FinalGame::HandleCollision, this, std::placeholders::_1, std::placeholders::_2));
}

void FinalGame::StartGameplay()
{
	LoadGameObjects();
}

void FinalGame::ProcessInput()
{
	float force = 0.5f;

	if (m_InputSystem.IsKeyPressed(KeyCode::W))
	{
		m_Player->GetComponent<RigidBody2D>()->AddForce(Vector2(0, force));
	}
	if (m_InputSystem.IsKeyPressed(KeyCode::A))
	{
		m_Player->GetComponent<RigidBody2D>()->AddForce(Vector2(-force, 0));
	}
	if (m_InputSystem.IsKeyPressed(KeyCode::S))
	{
		m_Player->GetComponent<RigidBody2D>()->AddForce(Vector2(0, -force));
	}
	if (m_InputSystem.IsKeyPressed(KeyCode::D))
	{
		m_Player->GetComponent<RigidBody2D>()->AddForce(Vector2(force, 0));
	}

	//if (m_InputSystem.IsKeyPressed(KeyCode::Y))
	//{
	//	monster->GetComponent<RigidBody2D>()->AddForce(Vector2(0, force));
	//}
	//if (m_InputSystem.IsKeyPressed(KeyCode::G))
	//{
	//	monster->GetComponent<RigidBody2D>()->AddForce(Vector2(-force, 0));
	//}
	//if (m_InputSystem.IsKeyPressed(KeyCode::H))
	//{
	//	monster->GetComponent<RigidBody2D>()->AddForce(Vector2(0, -force));
	//}
	//if (m_InputSystem.IsKeyPressed(KeyCode::J))
	//{
	//	monster->GetComponent<RigidBody2D>()->AddForce(Vector2(force, 0));
	//}

	if (m_InputSystem.IsKeyPressed(KeyCode::K))
	{
		m_Player->AddRotationZ(0.01f);
	}
	if (m_InputSystem.IsKeyPressed(KeyCode::L))
	{
		m_Player->AddRotationZ(-0.01f);
	}


	if (m_InputSystem.IsKeyDown(KeyCode::O))
	{
		SharedPointer<GameObject> newGameObject = m_ObjectGenerator.CreateGameObjectFromJSONDocument(m_JSONParser.GetJSONDocument("data/player.json"));
		m_GameWorld.AddGameObject(newGameObject);
	}
	if (m_InputSystem.IsKeyDown(KeyCode::P))
	{
		m_GameWorld.RemoveGameObjectAtIndex(m_GameWorld.GetGameObjectsCount() - 1);
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
			m_GameWorld.RemoveGameObject(monster);
		}
		EngineHelpers::DebugPrint("30 seconds elapsed.");
		gameTime = 0.0f;
	}*/
	float rotationSpeed = 0.5f;

	for (SharedPointer<GameObject> obstacle: m_ObstaclesList)
	{
		obstacle->AddRotationZ(rotationSpeed * m_DeltaTime);
	}
}

void FinalGame::ShutDownGameplay()
{
	RemoveAllObstacles();
}

void FinalGame::RemoveAllObstacles()
{
	for (SharedPointer<GameObject> obstacles : m_ObstaclesList)
	{
		if (obstacles)
		{
			obstacles->RemoveAllComponents();
		}
	}
	m_ObstaclesList.clear();
}

void FinalGame::HandleCollision(SharedPointer<GameObject> InObjectA, SharedPointer<GameObject> InObjectB)
{
	std::string objectAName = InObjectA->GetName();
	std::string objectBName = InObjectB->GetName();
	std::string logString = "Game Object " + objectAName + " collided with " + objectBName;

	EngineHelpers::DebugPrint(logString);

	if ((objectAName == "obstacle" && objectBName == "player") ||
		(objectAName == "player") && objectBName == "obstacle")
	{
		if (objectAName == "obstacle")
		{
			m_GameWorld.RemoveGameObject(InObjectA);
		}
		else
		{
			m_GameWorld.RemoveGameObject(InObjectB);
		}
		ChangeGameState(TGameState::kGameOver);
	}

	if ((objectAName == "goal" && objectBName == "player") ||
		(objectAName == "player") && objectBName == "goal")
	{		
		ChangeGameState(TGameState::kGameWon);
	}
}

void FinalGame::ChangeGameState(TGameState InGameState)
{
	if (m_CurrentGameState == InGameState)
	{
		return;
	}

	m_CurrentGameState = InGameState;

	switch (m_CurrentGameState)
	{
	case TGameState::kStart:
		break;
	case TGameState::kGameWon:
	{
		HideAllScreens();
		m_GameWonScreen->SetVisibility(true);
	}
		break;
	case TGameState::kGameOver:
	{
		HideAllScreens();
		m_GameOverScreen->SetVisibility(true);
	}
		break;
	default:
		break;
	}
}

void FinalGame::HideAllScreens()
{
	m_GameWonScreen->SetVisibility(false);
	m_GameOverScreen->SetVisibility(false);
}

void FinalGame::LoadGameObjects()
{
	std::string dataFilePath = "data/player.json";

	m_Player = CreateObject(dataFilePath);
	//m_Player->GetComponent<BoxCollider2D>()->EnableCollisionCallback([this](SharedPointer<GameObject> CollidedObject) {
	//	EngineHelpers::DebugPrint(CollidedObject->GetName());
	//	RigidBody2D& rigidbody = *(this->m_Player->GetComponent<RigidBody2D>());
	//	Vector2 velocity = rigidbody.GetVelocity();
	//	Vector2 force = rigidbody.GetForce();
	//	//rigidbody.AddForce(force * -2.0f);
	//	//rigidbody.SetVelocity(Vector2::Zero);
	//	//rigidbody.SetForce(Vector2::Zero);
	//	this->m_Direction = this->m_Direction * -1.0f;
	//	});

	dataFilePath = "data/goal.json";
	m_Goal = CreateObject(dataFilePath);

	dataFilePath = "data/obstacle.json";
	SharedPointer<GameObject> newObstacle = CreateObject(dataFilePath);
	m_ObstaclesList.push_back(newObstacle);

	Vector2 screenPosition = Vector2(0, float(-1 * ((int)(m_GameWindow.GetWindowHeight()) / 2)));
	dataFilePath = "data/gameover.json";
	m_GameOverScreen = CreateObject(dataFilePath);
	m_GameOverScreen->SetPosition(screenPosition);
	m_GameOverScreen->SetVisibility(false);

	dataFilePath = "data/gamewon.json";
	m_GameWonScreen = CreateObject(dataFilePath);
	m_GameWonScreen->SetPosition(screenPosition);
	m_GameWonScreen->SetVisibility(false);
}
