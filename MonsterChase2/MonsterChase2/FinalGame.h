#pragma once
#include "Game.h"
#include "SmartPointer/SmartPointer.h"
#include "Object/GameObject.h"
#include "Object/ObjectGenerator.h"
#include "FileLoader/JSONParser.h"
#include "Math/Vector2.h"

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

	SharedPointer<GameObject> player;
	SharedPointer<GameObject> monster;

	ObjectGenerator objectGenerator;
	JSONParser jsonParser;

	float gameTime = 0;

	Vector2 direction = Vector2::Zero;
};