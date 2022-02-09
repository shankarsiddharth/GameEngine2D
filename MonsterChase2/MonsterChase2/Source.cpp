#include <Windows.h>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "MonsterChaseGame.h"


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//_CrtSetBreakAlloc(224);
	
	{
		MonsterChaseGame game;
		game.StartGame(i_hInstance, i_nCmdShow);
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 0;

}