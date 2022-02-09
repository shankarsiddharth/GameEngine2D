#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

#include <DirectXColors.h>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include <chrono>
#include <conio.h>
#include <tchar.h>
#include <string>

#include "GLib.h"
#include "Monster.h"
#include "Player.h"
#include "DataStructure/LinkedList.h"
#include "Math/MathHelper.hpp"
#include "Time/EngineTime.h"
#include "FileLoader/FileLoader.h"


#define GAME_WINDOW_SIZE_X 800
#define GAME_WINDOW_SIZE_Y 600

#define PLAYER_SPEED 100
#define MONSTER_SPEED 1

int monsterDirection = std::rand() % 4;
int inputKeyCode = -1;



//void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
//GLib::Sprite* CreateSprite(const char* i_pFilename);
void KeyInputCallback(unsigned int i_VKeyID, bool bWentDown);
Monster* CreateNewMonster(int monster_count, int SizeX, int SizeY);
void MoveMonster(Monster* monsters, int SizeX, int SizeY);
void MovePlayer(Player& player, int inputKeyCode, int SizeX, int SizeY);
void MonsterChase(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow);
float GetFrameTime();

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//_CrtSetBreakAlloc(223);

	MonsterChase(i_hInstance, i_hPrevInstance, i_lpCmdLine, i_nCmdShow);

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}

void MonsterChase(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "MonsterChase2", -1, GAME_WINDOW_SIZE_X, GAME_WINDOW_SIZE_Y, true);

	if (bSuccess)
	{
		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(KeyInputCallback);

		//Initialize Engine
		EngineTime::Initialize();
		
		Player player;
		GLib::Sprite* pPlayerSprite = FileLoader::CreateSprite("data\\player.dds");

		Monster* monster = CreateNewMonster(0, GAME_WINDOW_SIZE_X / 2, GAME_WINDOW_SIZE_Y / 2);
		MoveMonster(monster, GAME_WINDOW_SIZE_X / 2, GAME_WINDOW_SIZE_Y / 2);
		GLib::Sprite* pMonsterSprite = FileLoader::CreateSprite("data\\monster.dds");

		bool bQuit = false;
		do
		{
			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);

			if (!bQuit)
			{
				float deltaTime = EngineTime::GetFrameTime();

				//Check the FPS
				float fps = (1.0f / deltaTime);
				//std::string fpsString = std::to_string(fps) + "\n";
				//OutputDebugStringA(fpsString.c_str());
				//OutputDebugString(_T(std::to_string(fps)));

				//TODO: Process Input
				if (inputKeyCode != -1)
				{
					MovePlayer(player, inputKeyCode, GAME_WINDOW_SIZE_X / 2, GAME_WINDOW_SIZE_Y / 2);
					inputKeyCode = -1;
				}

				// IMPORTANT: Tell GLib that we want to start rendering
				GLib::BeginRendering(DirectX::Colors::Blue);
				// Tell GLib that we want to render some sprites
				GLib::Sprites::BeginRendering();

				//TODO: Update Sprite Positions
				GLib::Point2D playerPosition{ (float)(player.GetPosition().X()), (float)(player.GetPosition().Y()) };
				if (pPlayerSprite)
				{
					GLib::Render(*pPlayerSprite, playerPosition, 0.0f, 0.0f);
				}

				MoveMonster(monster, GAME_WINDOW_SIZE_X / 2, GAME_WINDOW_SIZE_Y / 2);
				GLib::Point2D monsterPosition{ (float)(monster->GetPosition().X()), (float)(monster->GetPosition().Y()) };
				if (pMonsterSprite)
				{
					GLib::Render(*pMonsterSprite, monsterPosition, 0.0f, 0.0f);
				}

				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// IMPORTANT: Tell GLib we're done rendering
				GLib::EndRendering();
			}

		} while (bQuit == false);

		if (pPlayerSprite)
		{
			GLib::Release(pPlayerSprite);
		}
		if (pMonsterSprite)
		{
			GLib::Release(pMonsterSprite);
		}
		if (monster)
		{
			delete monster;
			monster = nullptr;
		}

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}
}


void KeyInputCallback(unsigned int i_VKeyID, bool bWentDown)
{
	inputKeyCode = i_VKeyID;
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

Monster* CreateNewMonster(int monster_count, int SizeX, int SizeY)
{
	Monster* newMonster = new Monster();
	int newX = GetRandomNumberInRange(SizeX, -SizeX);
	int newY = GetRandomNumberInRange(SizeY, -SizeY);
	newMonster->SetPosition(Point2D(newX, newY));
	return newMonster;
}

void MoveMonster(Monster* monster, int SizeX, int SizeY)
{
	Point2D deltaPosition;
	switch (monsterDirection)
	{
	case 0:
	{
		deltaPosition = Point2D(0, MONSTER_SPEED);
	}
	break;
	case 1:
	{
		deltaPosition = Point2D(-MONSTER_SPEED, 0);
	}
	break;
	case 2:
	{
		deltaPosition = Point2D(0, -MONSTER_SPEED);
	}
	break;
	case 3:
	default:
	{
		deltaPosition = Point2D(MONSTER_SPEED, 0);
	}
	break;
	}
	Point2D newPos = monster->GetPosition() + deltaPosition;
	if (newPos.X() < -SizeX)
	{
		monsterDirection = std::rand() % 4;
		newPos.X(-SizeX);
	}
	else if (newPos.X() > SizeX)
	{
		monsterDirection = std::rand() % 4;
		newPos.X(SizeX);
	}
	if (newPos.Y() < -SizeY)
	{
		monsterDirection = std::rand() % 4;
		newPos.Y(-SizeY);
	}
	else if (newPos.Y() > SizeY)
	{
		monsterDirection = std::rand() % 4;
		newPos.Y(SizeY);
	}
	monster->SetPosition(newPos);
}

void MovePlayer(Player& player, int inputKeyCode, int SizeX, int SizeY)
{
	Point2D deltaPosition;

	switch (inputKeyCode)
	{
	case 65: //A
	case 37: //Left
	{
		deltaPosition = Point2D(-MONSTER_SPEED, 0);
	}
	break;

	case 87: //W
	case 38: //Up
	{
		deltaPosition = Point2D(0, MONSTER_SPEED);
	}
	break;
	case 68: //D
	case 39: //Right
	{
		deltaPosition = Point2D(MONSTER_SPEED, 0);
	}
	break;
	case 83: //S
	case 40: //Down
	{
		deltaPosition = Point2D(0, -MONSTER_SPEED);
	}
	break;
	}
	Point2D newPos = player.GetPosition() + deltaPosition;
	if (newPos.X() < -SizeX)
	{
		newPos.X(SizeX);
	}
	else if (newPos.X() > SizeX)
	{
		newPos.X(0);
	}
	if (newPos.Y() < -SizeY)
	{
		newPos.Y(SizeY);
	}
	else if (newPos.Y() > SizeY)
	{
		newPos.Y(0);
	}
	player.SetPosition(newPos);
}

