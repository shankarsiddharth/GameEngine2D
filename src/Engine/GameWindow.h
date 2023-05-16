#pragma once

#include <Windows.h>
#include <string>

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	bool Initialize(HINSTANCE InHInstance, int InNCmdShow,
		std::string InWindowName = "DefaultGameWindow",
		unsigned int InWindowWidth = DEFAULT_GAME_WINDOW_WIDTH_SIZE_X,
		unsigned int InWindowHeight = DEFAULT_GAME_WINDOW_HEIGHT_SIZE_Y);
	void Update();
	void ShutDown();

	bool IsWindowClosed();

	std::string GetWindowName() const;
	void SetWindowName(std::string InWindowName);

	unsigned int GetWindowHeight() const;
	void SetWindowHeight(unsigned int InWindowHeight);
	unsigned int GetWindowWidth() const;
	void SetWindowWidth(unsigned int InWindowWidth);

private:
	bool m_IsWindowClosed = false;

	std::string m_WindowName = "";

	unsigned int m_WindowHeight = 0;
	unsigned int m_WindowWidth = 0;


	static const unsigned int DEFAULT_GAME_WINDOW_WIDTH_SIZE_X = 800;
	static const unsigned int DEFAULT_GAME_WINDOW_HEIGHT_SIZE_Y = 600;
};

