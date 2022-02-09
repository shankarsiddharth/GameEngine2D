#pragma once

#include <Windows.h>
#include <string>

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	/*bool Initialize(HINSTANCE i_hInstance, int i_nCmdShow, 
		std::string i_WindowName = DEFAULT_WINDOW_TITLE, 
		unsigned int i_WindowWidth = DEFAULT_GAME_WINDOW_WIDTH_SIZE_X,
		unsigned int i_WindowHeight = DEFAULT_GAME_WINDOW_HEIGHT_SIZE_Y);*/
	bool Initialize(HINSTANCE i_hInstance, int i_nCmdShow,
		std::string i_WindowName = "DefaultGameWindow",
		unsigned int i_WindowWidth = 800,
		unsigned int i_WindowHeight = 600);
	void Update();
	void ShutDown();

	bool IsWindowClosed();

private:
	bool bIsWindowClosed = false;

	/*static const unsigned int DEFAULT_GAME_WINDOW_WIDTH_SIZE_X;
	static const unsigned int DEFAULT_GAME_WINDOW_HEIGHT_SIZE_Y;
	static const std::string DEFAULT_WINDOW_TITLE*/;
};

