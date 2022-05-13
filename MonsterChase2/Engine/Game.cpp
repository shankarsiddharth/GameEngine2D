#include "Game.h"
#include "JobSystem/JobSystem/JobSystem.h"

Game::Game()
	:GameRuntime()
{
	
}

Game::~Game()
{
	
}

void Game::StartGame(HINSTANCE InHInstance, int InNCmdShow)
{
	InitializeGameplay();
	bool isRuntimeInitialized = Initialize(InHInstance, InNCmdShow);
	if (isRuntimeInitialized)
	{
		StartGameplay();
		UpdateGame();
		ExitGame();
	}
}

SharedPointer<GameObject> Game::CreateObject(std::string InFilePath)
{
	SharedPointer<GameObject> newGameObject;

	Engine::JobSystem::JobStatus jobStatus;

	Engine::JobSystem::RunJob(
		Engine::JobSystem::GetDefaultQueueName(),
		[this, InFilePath, &newGameObject]()
		{
			this->m_JSONParser.GetFileContentsAsync(InFilePath, [this, &newGameObject](std::string contents) {
				newGameObject = m_ObjectGenerator.CreateGameObjectFromJSONDocument(
					m_JSONParser.GetJSONDocumentFromString(contents)
				);
				this->m_GameWorld.AddGameObject(newGameObject);
				});
		},
		&jobStatus
			);

	jobStatus.WaitForZeroJobsLeft();

	return newGameObject;
}

void Game::UpdateGame()
{
	do
	{
		UpdateDeltaTime();
		Update();
		UpdateInput();
		UpdateGameplay();
	} while (IsRunning());
}

void Game::ExitGame()
{
	ShutDownGameplay();
	ShutDown();
}
