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
	void CreateBreakableWalls();
	void CreateObstacles();
	void CreateWalls();
	void CreateGoal();
	void CreatePlayer();

	void UpdateObstacleRotation();
	
	void RemoveAllObstacles();
	void RemoveAllBreakableWalls();
	void RemoveAllWalls();
	void HandleCollision(SharedPointer<GameObject> InObjectA, SharedPointer<GameObject> InObjectB);

	void ChangeGameState(TGameState InGameState);
	void HideAllScreens();
	
	SharedPointer<GameObject> m_Player;
	SharedPointer<GameObject> m_Goal;
	std::vector<SharedPointer<GameObject>> m_ObstaclesList;
	std::vector<SharedPointer<GameObject>> m_BrekableWallsList;
	std::vector<SharedPointer<GameObject>> m_WallsList;

	SharedPointer<GameObject> m_GameOverScreen;
	SharedPointer<GameObject> m_GameWonScreen;

	TGameState m_CurrentGameState;

	GameConstants m_GameConstants;

	float m_GameTime = 0;
	Vector2 m_Direction = Vector2::Zero;
};