#pragma once
#include "KeyCode.h"
#include <map>
#include <vector>

class InputSystem
{
public:
	void Initialize();

	void UpdateInput();
	void ClearInput();
	bool IsValidInput();

	bool IsKeyDown(KeyCode i_Key);
	bool IsKeyUp(KeyCode i_Key);
	bool IsKeyPressed(KeyCode i_Key);

	KeyCode GetCurrentKeyCode();

private:
	
	void KeyInputCallback(unsigned int i_VKeyID, bool bWentDown);

	//int previousInputKeyCode = -1;
	//bool previousIsUp = false;
	//bool previousIsDown = false;

	int inputKeyCode = -1;
	bool isUp = false;
	bool isDown = false;

	std::map<KeyCode, bool> keyPressedMap;
	std::vector<KeyCode> validKeyCodes;
};