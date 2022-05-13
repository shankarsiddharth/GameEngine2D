#pragma once

#include "GameRuntime.h"
#include "Object/ObjectGenerator.h"
#include "FileLoader/JSONParser.h"
#include <string>
#include "SmartPointer/SmartPointer.h"
#include "Object/GameObject.h"

class Game :
	public GameRuntime
{
public:
	Game();
	~Game();

	void StartGame(HINSTANCE InHInstance, int InNCmdShow);
	
protected:
	virtual void ProcessInput() = 0;
	virtual void InitializeGameplay() = 0;
	virtual void StartGameplay() = 0;
	virtual void UpdateGameplay() = 0;
	virtual void ShutDownGameplay() = 0;

	SharedPointer<GameObject> CreateObject(std::string InFilePath);

	ObjectGenerator m_ObjectGenerator;
	JSONParser m_JSONParser;

private:
	void UpdateGame();
	void ExitGame();

};

