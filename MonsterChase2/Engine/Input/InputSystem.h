#pragma once
#include "KeyCode.h"

class InputSystem
{
public:
	void Initialize();
	void Update();

	bool IsKeyDown(KeyCode i_Key);
	bool IsKeyUp(KeyCode i_Key);

	KeyCode GetCurrentKeyCode();

private:
	void KeyInputCallback(unsigned int i_VKeyID, bool bWentDown);
	
	int inputKeyCode = -1;
	bool isUp = false;
	bool isDown = false;
};