#pragma once
#include "Game.h"
#include "SmartPointer/SmartPointer.h"
#include "Object/GameObject.h"
#include "Math/Vector2.h"
#include <vector>

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

	SharedPointer<GameObject> m_Player;
	SharedPointer<GameObject> m_Goal;
	std::vector<SharedPointer<GameObject>> m_ObstaclesList;

	float gameTime = 0;
	Vector2 direction = Vector2::Zero;
};