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
	float force = m_GameConstants.PlayerForce;

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

	if (m_InputSystem.IsKeyPressed(KeyCode::K))
	{
		m_Player->AddRotationZ(0.01f);
	}
	if (m_InputSystem.IsKeyPressed(KeyCode::L))
	{
		m_Player->AddRotationZ(-0.01f);
	}


	//if (m_InputSystem.IsKeyDown(KeyCode::O))
	//{
	//	SharedPointer<GameObject> newGameObject = m_ObjectGenerator.CreateGameObjectFromJSONDocument(m_JSONParser.GetJSONDocument("data/player.json"));
	//	m_GameWorld.AddGameObject(newGameObject);
	//}
	//if (m_InputSystem.IsKeyDown(KeyCode::P))
	//{
	//	m_GameWorld.RemoveGameObjectAtIndex(m_GameWorld.GetGameObjectsCount() - 1);
	//}

}

void FinalGame::UpdateGameplay()
{
	UpdateObstacleRotation();
}

void FinalGame::ShutDownGameplay()
{
	RemoveAllGameplayObjects();
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

	//Player - Collectibles - Destroy the Collectible
	if ((objectAName == "collectible" && objectBName == "player") ||
		(objectAName == "player") && objectBName == "collectible")
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

	//Player - Boundary - Game Over
	if ((objectAName == "boundary" && objectBName == "player") ||
		(objectAName == "player") && objectBName == "boundary")
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

	//Player - Wall - Set the force to Zero
	if ((objectAName == "wall" && objectBName == "player") ||
		(objectAName == "player") && objectBName == "wall")
	{
		m_Player->GetComponent<RigidBody2D>()->SetForce(Vector2::Zero);
	}

}

void FinalGame::UpdateObstacleRotation()
{
	float rotationSpeed = m_GameConstants.ObstacleRotaionSpeed;

	for (SharedPointer<GameObject> obstacle : m_ObstaclesList)
	{
		obstacle->AddRotationZ(rotationSpeed * m_DeltaTime);
	}
}

void FinalGame::RemoveAllGameplayObjects()
{
	RemoveGameplayObjects(m_CollectiblesList);
	RemoveGameplayObjects(m_ObstaclesList);
	RemoveGameplayObjects(m_BrekableWallsList);
	RemoveGameplayObjects(m_WallsList);
}

void FinalGame::RemoveGameplayObjects(std::vector<SharedPointer<GameObject>>& m_ObjectsList)
{
	for (SharedPointer<GameObject> object : m_ObjectsList)
	{
		if (object)
		{
			object->RemoveAllComponents();
		}
	}
	m_ObjectsList.clear();
}

void FinalGame::ChangeGameState(TGameState InGameState)
{
	if (m_CurrentGameState == InGameState)
	{
		return;
	}

	switch (InGameState)
	{
	case TGameState::kStart:
		break;
	case TGameState::kGameWon:
	{
		if (m_CurrentGameState != TGameState::kGameOver)
		{
			m_Player->SetPosition(m_GameConstants.PlayerPosition);
			m_Player->GetComponent<RigidBody2D>()->SetForce(Vector2::Zero);
			HideAllScreens();
			m_GameWonScreen->SetVisibility(true);
		}
	}
	break;
	case TGameState::kGameOver:
	{
		if (m_CurrentGameState != TGameState::kGameWon)
		{
			HideAllScreens();
			m_GameOverScreen->SetVisibility(true);
		}
	}
	break;
	default:
		break;
	}

	m_CurrentGameState = InGameState;

}

void FinalGame::HideAllScreens()
{
	m_GameWonScreen->SetVisibility(false);
	m_GameOverScreen->SetVisibility(false);
}

void FinalGame::LoadGameObjects()
{
	CreateWorldBoundaries();
	CreatePlayer();
	CreateGoal();
	CreateCollectibles();
	//CreateWalls();
	CreateObstacles();
	//CreateBreakableWalls();
	CreateScreens();
}

void FinalGame::CreateWorldBoundaries()
{
	std::string dataFilePath = "data/heightboundary.json";
	for (size_t index = 0; index < m_GameConstants.HeightBoundaryPositions.size(); index++)
	{
		SharedPointer<GameObject> newBoundary = CreateObject(dataFilePath);
		newBoundary->SetPosition(m_GameConstants.HeightBoundaryPositions[index]);
		m_WorldBoundaryList.push_back(newBoundary);
	}

	dataFilePath = "data/widthboundary.json";
	for (size_t index = 0; index < m_GameConstants.WidthBoundaryPositions.size(); index++)
	{
		SharedPointer<GameObject> newBoundary = CreateObject(dataFilePath);
		newBoundary->SetPosition(m_GameConstants.WidthBoundaryPositions[index]);
		m_WorldBoundaryList.push_back(newBoundary);
	}
}

void FinalGame::CreateScreens()
{
	Vector2 screenPosition = Vector2(0, float(-1 * ((int)(m_GameWindow.GetWindowHeight()) / 2)));
	std::string dataFilePath = "data/gameover.json";
	m_GameOverScreen = CreateObject(dataFilePath);
	m_GameOverScreen->SetPosition(screenPosition);
	m_GameOverScreen->SetVisibility(false);

	dataFilePath = "data/gamewon.json";
	m_GameWonScreen = CreateObject(dataFilePath);
	m_GameWonScreen->SetPosition(screenPosition);
	m_GameWonScreen->SetVisibility(false);
}

void FinalGame::CreatePlayer()
{
	std::string dataFilePath = "data/player.json";
	m_Player = CreateObject(dataFilePath);
}

void FinalGame::CreateGoal()
{
	std::string dataFilePath = "data/goal.json";
	m_Goal = CreateObject(dataFilePath);
}

void FinalGame::CreateWalls()
{
	std::string dataFilePath = "data/wall.json";
	for (size_t index = 0; index < m_GameConstants.WallPositions.size(); index++)
	{
		SharedPointer<GameObject> newWall = CreateObject(dataFilePath);
		newWall->SetPosition(m_GameConstants.WallPositions[index]);
		m_WallsList.push_back(newWall);
	}
}

void FinalGame::CreateCollectibles()
{
	std::string dataFilePath = "data/breakablewall.json";
	for (size_t index = 0; index < m_GameConstants.CollectiblePositions.size(); index++)
	{
		SharedPointer<GameObject> newBreakableWall = CreateObject(dataFilePath);
		newBreakableWall->SetPosition(m_GameConstants.BreakableWallPositions[index]);
		m_BrekableWallsList.push_back(newBreakableWall);
	}
}

void FinalGame::CreateBreakableWalls()
{
	std::string dataFilePath = "data/breakablewall.json";
	for (size_t index = 0; index < m_GameConstants.BreakableWallPositions.size(); index++)
	{
		SharedPointer<GameObject> newBreakableWall = CreateObject(dataFilePath);
		newBreakableWall->SetPosition(m_GameConstants.BreakableWallPositions[index]);
		m_BrekableWallsList.push_back(newBreakableWall);
	}
}

void FinalGame::CreateObstacles()
{
	std::string dataFilePath = "data/obstacle.json";
	for (size_t index = 0; index < m_GameConstants.ObstaclePositions.size(); index++)
	{
		SharedPointer<GameObject> newObstacle = CreateObject(dataFilePath);
		newObstacle->SetPosition(m_GameConstants.ObstaclePositions[index]);
		m_ObstaclesList.push_back(newObstacle);
	}
}
