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
	UpdateObstacleRotation();

}

void FinalGame::UpdateObstacleRotation()
{
	float rotationSpeed = m_GameConstants.ObstacleRotaionSpeed;

	for (SharedPointer<GameObject> obstacle : m_ObstaclesList)
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

	//Player - Boundary - Stop the Player
	if ((objectAName == "boundary" && objectBName == "player") ||
		(objectAName == "player") && objectBName == "boundary")
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

void FinalGame::LoadGameObjects()
{
	CreateWorldBoundaries();
	CreatePlayer();
	CreateGoal();
	CreateWalls();
	CreateObstacles();
	CreateBreakableWalls();
	CreateScreens();
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

void FinalGame::CreateGoal()
{
	std::string dataFilePath = "data/goal.json";
	m_Goal = CreateObject(dataFilePath);
}

void FinalGame::CreatePlayer()
{
	std::string dataFilePath = "data/player.json";
	m_Player = CreateObject(dataFilePath);
}
