#include "FinalGame.h"
#include "GameRuntime.h"
#include "Object/GameObject.h"
#include "Component/Sprite2D.h"
#include "Component/RigidBody2D.h"
#include "JobSystem/JobSystem/JobSystem.h"
#include "Helpers/EngineHelpers.h"
#include "Component/BoxCollider2D.h"
#include "JobSystem/JobSystem/JobStatus.h"
#include "GameConstants.h"

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
	float force = GameConstants::PlayerForce;

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
	float rotationSpeed = GameConstants::ObstacleRotaionSpeed;

	for (SharedPointer<GameObject> obstacle: m_ObstaclesList)
	{
		obstacle->AddRotationZ(rotationSpeed * m_DeltaTime);
	}
}

void FinalGame::ShutDownGameplay()
{
	RemoveAllObstacles();
	RemoveAllBreakableWalls();
	RemoveAllWalls();
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

void FinalGame::RemoveAllBreakableWalls()
{
	for (SharedPointer<GameObject> breakableWalls : m_BrekableWallsList)
	{
		if (breakableWalls)
		{
			breakableWalls->RemoveAllComponents();
		}
	}
	m_BrekableWallsList.clear();
}

void FinalGame::RemoveAllWalls()
{
	for (SharedPointer<GameObject> walls : m_WallsList)
	{
		if (walls)
		{
			walls->RemoveAllComponents();
		}
	}
	m_WallsList.clear();
}

void FinalGame::HandleCollision(SharedPointer<GameObject> InObjectA, SharedPointer<GameObject> InObjectB)
{
	std::string objectAName = InObjectA->GetName();
	std::string objectBName = InObjectB->GetName();
	std::string logString = "Game Object " + objectAName + " collided with " + objectBName;

	EngineHelpers::DebugPrint(logString);

	//Player - Goal - Game Won
	if ((objectAName == "goal" && objectBName == "player") ||
		(objectAName == "player") && objectBName == "goal")
	{
		ChangeGameState(TGameState::kGameWon);
	}

	//Player - Obstacle - Game Over
	if ((objectAName == "obstacle" && objectBName == "player") ||
		(objectAName == "player") && objectBName == "obstacle")
	{		
		ChangeGameState(TGameState::kGameOver);
	}

	//Player - BreakableWall - Destroy the Wall
	if ((objectAName == "breakablewall" && objectBName == "player") ||
		(objectAName == "player") && objectBName == "breakablewall")
	{
		if (InObjectA == m_Player)
		{
			m_GameWorld.RemoveGameObject(InObjectB);
		}
		else
		{
			m_GameWorld.RemoveGameObject(InObjectA);
		}
	}		

	//Player - Wall - Stop the Player
	if ((objectAName == "wall" && objectBName == "player") ||
		(objectAName == "player") && objectBName == "wall")
	{
		m_Player->GetComponent<RigidBody2D>()->SetForce(Vector2::Zero);
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

	dataFilePath = "data/goal.json";
	m_Goal = CreateObject(dataFilePath);

	dataFilePath = "data/wall.json";
	SharedPointer<GameObject> newWall = CreateObject(dataFilePath);
	m_WallsList.push_back(newWall);

	dataFilePath = "data/obstacle.json";
	SharedPointer<GameObject> newObstacle = CreateObject(dataFilePath);
	m_ObstaclesList.push_back(newObstacle);

	dataFilePath = "data/breakablewall.json";
	SharedPointer<GameObject> newBreakableWall = CreateObject(dataFilePath);
	m_BrekableWallsList.push_back(newBreakableWall);

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
