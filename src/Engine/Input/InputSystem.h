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

	bool IsKeyDown(KeyCode InKey);
	bool IsKeyUp(KeyCode InKey);
	bool IsKeyPressed(KeyCode InKey);

	KeyCode GetCurrentKeyCode();

private:
	
	void KeyInputCallback(unsigned int InVKeyID, bool InIsDown);

	int m_InputKeyCode = -1;
	bool m_IsUp = false;
	bool m_IsDown = false;

	std::map<KeyCode, bool> m_KeyPressedMap;
	std::vector<KeyCode> m_ValidKeyCodesList;
};