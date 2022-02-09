#pragma once

#include <Windows.h>
#include <string>

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	bool Initialize(HINSTANCE i_hInstance, int i_nCmdShow,
		std::string i_WindowName = "DefaultGameWindow",
		unsigned int i_WindowWidth = DEFAULT_GAME_WINDOW_WIDTH_SIZE_X,
		unsigned int i_WindowHeight = DEFAULT_GAME_WINDOW_HEIGHT_SIZE_Y);
	void Update();
	void ShutDown();

	bool IsWindowClosed();

private:
	bool bIsWindowClosed = false;

	static const unsigned int DEFAULT_GAME_WINDOW_WIDTH_SIZE_X = 800;
	static const unsigned int DEFAULT_GAME_WINDOW_HEIGHT_SIZE_Y = 600;
};

