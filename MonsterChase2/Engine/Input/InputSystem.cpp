#include "InputSystem.h"
#include "../../GLib/GLib.h"

void InputSystem::Initialize()
{
	GLib::SetKeyStateChangeCallback(std::bind(&InputSystem::KeyInputCallback, this, std::placeholders::_1,std::placeholders:: _2));
}

void InputSystem::Update()
{
	inputKeyCode = -1;
	isDown = false;
	isUp = false;
}

bool InputSystem::IsKeyDown(KeyCode i_Key)
{
	if (GetCurrentKeyCode() == i_Key
		&& isDown)
	{
		return true;
	}
	return false;
}

bool InputSystem::IsKeyUp(KeyCode i_Key)
{
	if (GetCurrentKeyCode() == i_Key
		&& isUp)
	{
		return true;
	}
	return false;
}

void InputSystem::KeyInputCallback(unsigned int i_VKeyID, bool bWentDown)
{
	inputKeyCode = i_VKeyID;
	isDown = bWentDown;
	isUp = !bWentDown;
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

KeyCode InputSystem::GetCurrentKeyCode()
{
	return (KeyCode)(inputKeyCode);
}
