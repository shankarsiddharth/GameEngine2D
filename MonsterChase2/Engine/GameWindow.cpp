#include "GameWindow.h"
#include "../GLib/GLib.h"

GameWindow::GameWindow()
{

}

GameWindow::~GameWindow()
{
	
}

bool GameWindow::Initialize(HINSTANCE i_hInstance, int i_nCmdShow, 
	std::string i_WindowName /*= "DefaultGameWindow"*/, 
	unsigned int i_WindowWidth /*= DEFAULT_GAME_WINDOW_WIDTH_SIZE_X*/, 
	unsigned int i_WindowHeight /*= DEFAULT_GAME_WINDOW_HEIGHT_SIZE_Y*/)
{
	if (WindowHeight != 0)
	{
		i_WindowHeight = WindowHeight;
	}
	if (WindowWidth != 0)
	{
		i_WindowWidth = WindowWidth;
	}
	if (WindowName != "")
	{
		i_WindowName = WindowName;
	}

	// IMPORTANT: first we need to initialize GLib
	return GLib::Initialize(i_hInstance, i_nCmdShow, i_WindowName.c_str(), -1, i_WindowWidth, i_WindowHeight, true);
}

void GameWindow::Update()
{
	// IMPORTANT: Check whether the window is closed.
	GLib::Service(bIsWindowClosed);
}

void GameWindow::ShutDown()
{
	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	GLib::Shutdown();
}

bool GameWindow::IsWindowClosed()
{
	return bIsWindowClosed;
}

std::string GameWindow::GetWindowName() const
{
	return WindowName;
}

void GameWindow::SetWindowName(std::string i_WindowName)
{
	WindowName = i_WindowName;
}

unsigned int GameWindow::GetWindowHeight() const
{
	return WindowHeight;
}

void GameWindow::SetWindowHeight(unsigned int i_WindowHeight)
{
	WindowHeight = i_WindowHeight;
}

unsigned int GameWindow::GetWindowWidth() const
{
	return WindowWidth;
}

void GameWindow::SetWindowWidth(unsigned int i_WindowWidth)
{
	WindowWidth = i_WindowWidth;
}

