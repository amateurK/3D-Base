
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���͊Ǘ��N���X
// 
// �����	: amateurK
// �쐬��	: 2024/11/21
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "InputManager.h"

namespace AK_Base {

	InputManager* InputManager::Instance = nullptr;

	InputManager::InputManager()
	{
		for (int i = 0; i < 256; i++) {
			m_KeyState[0][i] = 0;
			m_KeyState[1][i] = 0;
		}
		m_NowSlot = 0;
	}

	//--------------------------------------------------------------------------------------
	InputManager::~InputManager()
	{
	}

	//---------------------------------------------------------------------------------------------
	void InputManager::Update()
	{
		// bit���]
		m_NowSlot ^= 1;

		// �L�[���X�V
		auto result = GetKeyboardState(m_KeyState[m_NowSlot]);
	}

	//---------------------------------------------------------------------------------------------
	bool InputManager::IsKeyPressed(int id)
	{
		return ((m_KeyState[m_NowSlot][id] & 0x80) == 0x80);
	}

	//---------------------------------------------------------------------------------------------
	bool InputManager::IsKeyReleased(int id)
	{
		return ((m_KeyState[m_NowSlot][id] & 0x80) == 0x00);
	}

	//---------------------------------------------------------------------------------------------
	bool InputManager::IsKeyNowPressed(int id)
	{
		return ((m_KeyState[m_NowSlot][id] & 0x80) == 0x80) &&
			((m_KeyState[!m_NowSlot][id] & 0x80) == 0x00);
	}

	//---------------------------------------------------------------------------------------------
	bool InputManager::IsKeyNowReleased(int id)
	{
		return ((m_KeyState[m_NowSlot][id] & 0x80) == 0x00) &&
			((m_KeyState[!m_NowSlot][id] & 0x80) == 0x80);
	}
}