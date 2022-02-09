#include "GameWindow.h"
#include "../GLib/GLib.h"

//const unsigned int GameWindow::DEFAULT_GAME_WINDOW_WIDTH_SIZE_X = 800;
//const unsigned int GameWindow::DEFAULT_GAME_WINDOW_HEIGHT_SIZE_Y = 600;
//const std::string GameWindow::DEFAULT_WINDOW_TITLE = std::string("DefaultGameWindow");

GameWindow::GameWindow()
{

}

GameWindow::~GameWindow()
{
	
}

bool GameWindow::Initialize(HINSTANCE i_hInstance, int i_nCmdShow, 
	std::string i_WindowName /*= DEFAULT_WINDOW_TITLE*/, 
	unsigned int i_WindowWidth /*= DEFAULT_GAME_WINDOW_WIDTH_SIZE_X*/, 
	unsigned int i_WindowHeight /*= DEFAULT_GAME_WINDOW_HEIGHT_SIZE_Y*/)
{
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

