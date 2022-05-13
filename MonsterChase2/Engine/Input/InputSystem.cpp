#include "InputSystem.h"
#include "../../GLib/GLib.h"
#include "../Helpers/EngineHelpers.h"

void InputSystem::UpdateInput()
{

}

void InputSystem::ClearInput()
{
	m_InputKeyCode = -1;
	m_IsDown = false;
	m_IsUp = false;
}

bool InputSystem::IsValidInput()
{
	return m_InputKeyCode != -1;
}

bool InputSystem::IsKeyDown(KeyCode InKey)
{
	if (GetCurrentKeyCode() == InKey
		&& m_IsDown)
	{
		return true;
	}
	return false;
}

bool InputSystem::IsKeyUp(KeyCode InKey)
{
	if (GetCurrentKeyCode() == InKey
		&& m_IsUp)
	{
		return true;
	}
	return false;
}

bool InputSystem::IsKeyPressed(KeyCode i_Key)
{
	if (m_KeyPressedMap.count(i_Key))
	{		
		return m_KeyPressedMap[i_Key];
	}
	return false;
}

void InputSystem::KeyInputCallback(unsigned int InVKeyID, bool InIsDown)
{
	m_InputKeyCode = InVKeyID;
	m_IsDown = InIsDown;
	m_IsUp = !InIsDown;

	m_KeyPressedMap[(KeyCode)m_InputKeyCode] = m_IsDown;

#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", InVKeyID, InIsDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

KeyCode InputSystem::GetCurrentKeyCode()
{
	return (KeyCode)(m_InputKeyCode);
}

void InputSystem::Initialize()
{
	m_ValidKeyCodesList.push_back(KeyCode::Enter);
	m_ValidKeyCodesList.push_back(KeyCode::Escape);
	m_ValidKeyCodesList.push_back(KeyCode::Space);
	m_ValidKeyCodesList.push_back(KeyCode::A);
	m_ValidKeyCodesList.push_back(KeyCode::B);
	m_ValidKeyCodesList.push_back(KeyCode::C);
	m_ValidKeyCodesList.push_back(KeyCode::D);
	m_ValidKeyCodesList.push_back(KeyCode::E);
	m_ValidKeyCodesList.push_back(KeyCode::F);
	m_ValidKeyCodesList.push_back(KeyCode::G);
	m_ValidKeyCodesList.push_back(KeyCode::H);
	m_ValidKeyCodesList.push_back(KeyCode::I);
	m_ValidKeyCodesList.push_back(KeyCode::J);
	m_ValidKeyCodesList.push_back(KeyCode::K);
	m_ValidKeyCodesList.push_back(KeyCode::L);
	m_ValidKeyCodesList.push_back(KeyCode::M);
	m_ValidKeyCodesList.push_back(KeyCode::N);
	m_ValidKeyCodesList.push_back(KeyCode::O);
	m_ValidKeyCodesList.push_back(KeyCode::P);
	m_ValidKeyCodesList.push_back(KeyCode::Q);
	m_ValidKeyCodesList.push_back(KeyCode::R);
	m_ValidKeyCodesList.push_back(KeyCode::S);
	m_ValidKeyCodesList.push_back(KeyCode::T);
	m_ValidKeyCodesList.push_back(KeyCode::U);
	m_ValidKeyCodesList.push_back(KeyCode::V);
	m_ValidKeyCodesList.push_back(KeyCode::W);
	m_ValidKeyCodesList.push_back(KeyCode::X);
	m_ValidKeyCodesList.push_back(KeyCode::Y);
	m_ValidKeyCodesList.push_back(KeyCode::Z);

	for (KeyCode keyCode : m_ValidKeyCodesList)
	{
		m_KeyPressedMap.insert(std::pair<KeyCode, bool>(keyCode, false));
	}

	GLib::SetKeyStateChangeCallback(std::bind(&InputSystem::KeyInputCallback, this, std::placeholders::_1, std::placeholders::_2));
}
