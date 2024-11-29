
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 入力管理クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/11/21
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "InputManager.h"

namespace AK_Base {

	InputManager* InputManager::Instance = nullptr;

	InputManager::InputManager()
		: m_NowSlot(0)
		, m_DirectInput(nullptr)
		, m_Keyboard(nullptr)
	{
		Init();
	}

	//--------------------------------------------------------------------------------------
	InputManager::~InputManager()
	{
		if (m_Keyboard.Get() != nullptr)
		{
			m_Keyboard->Unacquire();
		}
		m_Keyboard.Reset();
		m_DirectInput.Reset();
	}

	//---------------------------------------------------------------------------------------------
	HRESULT InputManager::Init()
	{
		HRESULT hr = S_OK;

		// キー入力の初期化
		for (int i = 0; i < 256; i++) {
			m_KeyState[0][i] = 0;
			m_KeyState[1][i] = 0;
		}
		m_NowSlot = 0;

		auto myGame(&AK_Base::BaseWindow::GetInstance());
		auto pHInst = myGame->GetHInstance();
		auto pHWnd = myGame->GetHWnd();


		// DirectInputの初期化
		hr = DirectInput8Create(*pHInst, DIRECTINPUT_VERSION, IID_IDirectInput8,
			(void**)m_DirectInput.ReleaseAndGetAddressOf(), nullptr);
		if (FAILED(hr))return hr;

		// キーボードの初期化
		hr = m_DirectInput->CreateDevice(GUID_SysKeyboard, m_Keyboard.ReleaseAndGetAddressOf(), nullptr);
		if (FAILED(hr))return hr;
		hr = m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr))return hr;
		hr = m_Keyboard->SetCooperativeLevel(*pHWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(hr))return hr;
		hr = m_Keyboard->Acquire();
		if (FAILED(hr))return hr;

		return hr;
	}

	//---------------------------------------------------------------------------------------------
	void InputManager::Update()
	{
		// bit反転
		m_NowSlot ^= 1;


		HRESULT hr = S_OK;
		// キーボードの入力状態を取得
		hr = m_Keyboard->GetDeviceState(KEY_NUM, m_KeyState[m_NowSlot]);

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