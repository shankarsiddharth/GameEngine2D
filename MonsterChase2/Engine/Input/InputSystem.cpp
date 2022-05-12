#include "InputSystem.h"
#include "../../GLib/GLib.h"

void InputSystem::UpdateInput()
{
	//previousIsDown = isDown;
	//previousIsDown = isUp;
	//previousInputKeyCode = inputKeyCode;
	//ClearInput();
}

void InputSystem::ClearInput()
{
	inputKeyCode = -1;
	isDown = false;
	isUp = false;
}

bool InputSystem::IsValidInput()
{
	return inputKeyCode != -1;
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

bool InputSystem::IsKeyPressed(KeyCode i_Key)
{
	for (KeyCode keyCode : validKeyCodes)
	{
		if (keyCode == i_Key)
		{
			return keyPressedMap[keyCode];
		}
	}
	return false;
}

void InputSystem::KeyInputCallback(unsigned int i_VKeyID, bool bWentDown)
{
	inputKeyCode = i_VKeyID;
	isDown = bWentDown;
	isUp = !bWentDown;

	keyPressedMap[(KeyCode)i_VKeyID] = isDown;

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

void InputSystem::Initialize()
{
	validKeyCodes.push_back(KeyCode::Enter);
	validKeyCodes.push_back(KeyCode::Escape);
	validKeyCodes.push_back(KeyCode::Space);
	validKeyCodes.push_back(KeyCode::A);
	validKeyCodes.push_back(KeyCode::B);
	validKeyCodes.push_back(KeyCode::C);
	validKeyCodes.push_back(KeyCode::D);
	validKeyCodes.push_back(KeyCode::E);
	validKeyCodes.push_back(KeyCode::F);
	validKeyCodes.push_back(KeyCode::G);
	validKeyCodes.push_back(KeyCode::H);
	validKeyCodes.push_back(KeyCode::I);
	validKeyCodes.push_back(KeyCode::J);
	validKeyCodes.push_back(KeyCode::K);
	validKeyCodes.push_back(KeyCode::L);
	validKeyCodes.push_back(KeyCode::M);
	validKeyCodes.push_back(KeyCode::N);
	validKeyCodes.push_back(KeyCode::O);
	validKeyCodes.push_back(KeyCode::P);
	validKeyCodes.push_back(KeyCode::Q);
	validKeyCodes.push_back(KeyCode::R);
	validKeyCodes.push_back(KeyCode::S);
	validKeyCodes.push_back(KeyCode::T);
	validKeyCodes.push_back(KeyCode::U);
	validKeyCodes.push_back(KeyCode::V);
	validKeyCodes.push_back(KeyCode::W);
	validKeyCodes.push_back(KeyCode::X);
	validKeyCodes.push_back(KeyCode::Y);
	validKeyCodes.push_back(KeyCode::Z);

	GLib::SetKeyStateChangeCallback(std::bind(&InputSystem::KeyInputCallback, this, std::placeholders::_1, std::placeholders::_2));
}
