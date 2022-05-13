#include "Game.h"
#include "JobSystem/JobSystem/JobSystem.h"

Game::Game()
	:GameRuntime()
{
	
}

Game::~Game()
{
	
}

void Game::StartGame(HINSTANCE i_hInstance, int i_nCmdShow)
{
	InitializeGameplay();
	bool isRuntimeInitialized = Initialize(i_hInstance, i_nCmdShow);
	if (isRuntimeInitialized)
	{
		StartGameplay();
		UpdateGame();
		ExitGame();
	}
}

SharedPointer<GameObject> Game::CreateObject(std::string i_FilePath)
{
	SharedPointer<GameObject> newGameObject;

	Engine::JobSystem::JobStatus Status;

	Engine::JobSystem::RunJob(
		Engine::JobSystem::GetDefaultQueueName(),
		[this, i_FilePath, &newGameObject]()
		{
			this->jsonParser.GetFileContentsAsync(i_FilePath, [this, &newGameObject](std::string contents) {
				newGameObject = objectGenerator.CreateGameObjectFromJSONDocument(
					jsonParser.GetJSONDocumentFromString(contents)
				);
				this->gameWorld.AddGameObject(newGameObject);
				});
		},
		&Status
			);

	Status.WaitForZeroJobsLeft();

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
