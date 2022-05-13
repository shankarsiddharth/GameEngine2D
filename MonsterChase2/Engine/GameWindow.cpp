#include "GameWindow.h"
#include "../GLib/GLib.h"

GameWindow::GameWindow()
{

}

GameWindow::~GameWindow()
{
	
}

bool GameWindow::Initialize(HINSTANCE InHInstance, int InNCmdShow, 
	std::string InWindowName /*= "DefaultGameWindow"*/, 
	unsigned int InWindowWidth /*= DEFAULT_GAME_WINDOW_WIDTH_SIZE_X*/, 
	unsigned int InWindowHeight /*= DEFAULT_GAME_WINDOW_HEIGHT_SIZE_Y*/)
{
	if (m_WindowHeight != 0)
	{
		InWindowHeight = m_WindowHeight;
	}
	if (m_WindowWidth != 0)
	{
		InWindowWidth = m_WindowWidth;
	}
	if (m_WindowName != "")
	{
		InWindowName = m_WindowName;
	}

	// IMPORTANT: first we need to initialize GLib
	return GLib::Initialize(InHInstance, InNCmdShow, InWindowName.c_str(), -1, InWindowWidth, InWindowHeight, true);
}

void GameWindow::Update()
{
	// IMPORTANT: Check whether the window is closed.
	GLib::Service(m_IsWindowClosed);
}

void GameWindow::ShutDown()
{
	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	GLib::Shutdown();
}

bool GameWindow::IsWindowClosed()
{
	return m_IsWindowClosed;
}

std::string GameWindow::GetWindowName() const
{
	return m_WindowName;
}

void GameWindow::SetWindowName(std::string InWindowName)
{
	m_WindowName = InWindowName;
}

unsigned int GameWindow::GetWindowHeight() const
{
	return m_WindowHeight;
}

void GameWindow::SetWindowHeight(unsigned int InWindowHeight)
{
	m_WindowHeight = InWindowHeight;
}

unsigned int GameWindow::GetWindowWidth() const
{
	return m_WindowWidth;
}

void GameWindow::SetWindowWidth(unsigned int InWindowWidth)
{
	m_WindowWidth = InWindowWidth;
}

