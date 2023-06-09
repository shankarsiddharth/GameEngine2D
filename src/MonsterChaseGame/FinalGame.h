#pragma once
#include "Game.h"
#include "SmartPointer/SmartPointer.h"
#include "Object/GameObject.h"
#include "Math/Vector2.h"
#include <vector>
#include "GameState.h"
#include "GameConstants.h"

class FinalGame
	: public Game
{
public:
	FinalGame();
	~FinalGame();

protected:
	void InitializeGameplay() override;
	void StartGameplay() override;
	void ProcessInput() override;
	void UpdateGameplay() override;
	void ShutDownGameplay() override;

private:
	void LoadGameObjects();

	void CreateScreens();
	void CreateSplashScreen();
	void CreateGameOverScreen();
	void CreateGameWonScreen();
	void CreateCollectibles();
	void CreateBreakableWalls();
	void CreateObstacles();
	void CreateWalls();
	void CreateGoal();
	void CreatePlayer();
	void CreateWorldBoundaries();

	void UpdateObstacleRotation();
	
	void RemoveAllGameplayObjects();
	void RemoveGameplayObjects(std::vector<SharedPointer<GameObject>>& m_ObjectsList);

	void HandleCollision(SharedPointer<GameObject> InObjectA, SharedPointer<GameObject> InObjectB);

	void ChangeGameState(TGameState InGameState);
	void HideAllScreens();
	
	SharedPointer<GameObject> m_Player;
	SharedPointer<GameObject> m_Goal;
	std::vector<SharedPointer<GameObject>> m_ObstaclesList;
	std::vector<SharedPointer<GameObject>> m_CollectiblesList;
	std::vector<SharedPointer<GameObject>> m_BrekableWallsList;
	std::vector<SharedPointer<GameObject>> m_WallsList;
	std::vector<SharedPointer<GameObject>> m_WorldBoundaryList;

	SharedPointer<GameObject> m_GameOverScreen;
	SharedPointer<GameObject> m_GameWonScreen;
	SharedPointer<GameObject> m_SplashScreen;

	TGameState m_CurrentGameState;

	GameConstants m_GameConstants;

	float m_GameTime = 0;
	Vector2 m_Direction = Vector2::Zero;
};