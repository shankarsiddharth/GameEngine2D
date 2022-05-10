#include <Windows.h>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "MonsterChaseGame.h"
#include "ThirdParty/nlohmann/json.hpp"
#include <iostream>

using json = nlohmann::json;

void RunGame(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	MonsterChaseGame game;
	game.StartGame(i_hInstance, i_nCmdShow);
}

void TestJSON()
{
	// create an empty structure (null)
	json j;

	// add a number that is stored as double (note the implicit conversion of j to an object)
	j["pi"] = 3.141;

	// add a Boolean that is stored as bool
	j["happy"] = true;

	// add a string that is stored as std::string
	j["name"] = "Niels";

	// add another null object by passing nullptr
	j["nothing"] = nullptr;

	// add an object inside the object
	j["answer"]["everything"] = 42;

	// add an array that is stored as std::vector (using an initializer list)
	j["list"] = { 1, 0, 2 };

	// add another object (using an initializer list of pairs)
	j["object"] = { {"currency", "USD"}, {"value", 42.99} };

	// instead, you could also write (which looks very similar to the JSON above)
	json j2 = {
	  {"pi", 3.141},
	  {"happy", true},
	  {"name", "Niels"},
	  {"nothing", nullptr},
	  {"answer", {
		{"everything", 42}
	  }},
	  {"list", {1, 0, 2}},
	  {"object", {
		{"currency", "USD"},
		{"value", 42.99}
	  }}
	};

#ifdef _DEBUG
	const size_t	lenBuffer = 500;
	char			Buffer[lenBuffer];
	std::string s = j.dump();
	sprintf_s(Buffer, lenBuffer, "JSON: %s\n", s.c_str());
	OutputDebugStringA(Buffer);
#endif _DEBUG
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{	
	{
		TestJSON();
	}

	{
		RunGame(i_hInstance, i_hPrevInstance, i_lpCmdLine, i_nCmdShow);
	}

	

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 0;

}