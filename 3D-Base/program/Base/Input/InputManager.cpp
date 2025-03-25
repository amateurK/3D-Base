
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 入力管理クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/11/21
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "InputManager.h"
#include "../BaseWindow.h"

namespace AK_Base {

	InputManager* InputManager::Instance = nullptr;

	InputManager::InputManager()
		: m_NowSlot(0)
		, m_DirectInput(nullptr)
		, m_Keyboard(nullptr)
		, m_Mouse(nullptr)
		, m_IsCursorShown(true)
		, m_IsCursorClippedByWindow(false)
	{
		Init();
	}

	//--------------------------------------------------------------------------------------
	InputManager::~InputManager()
	{

		for (uint8_t i = 0; i < MAX_CONTROLLERS; i++) {
			if (m_Gamepad[i].Get() != nullptr)
			{
				m_Gamepad[i]->Unacquire();
			}
			m_Mouse.Reset();
		}
		if (m_Mouse.Get() != nullptr)
		{
			m_Mouse->Unacquire();
		}
		m_Mouse.Reset();
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
		for (int i = 0; i < BUTTON_NUM; i++) {
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

		{
			// キーボードの初期化
			hr = m_DirectInput->CreateDevice(GUID_SysKeyboard, m_Keyboard.ReleaseAndGetAddressOf(), nullptr);
			if (FAILED(hr))return hr;
			hr = m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
			if (FAILED(hr))return hr;
			hr = m_Keyboard->SetCooperativeLevel(*pHWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
			if (FAILED(hr))return hr;
			hr = m_Keyboard->Acquire();
			//if (FAILED(hr))return hr;
		}
		{
			// マウスの初期化
			hr = m_DirectInput->CreateDevice(GUID_SysMouse, m_Mouse.ReleaseAndGetAddressOf(), nullptr);
			if (FAILED(hr))return hr;
			hr = m_Mouse->SetDataFormat(&c_dfDIMouse);
			if (FAILED(hr))return hr;
			hr = m_Mouse->SetCooperativeLevel(*pHWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
			if (FAILED(hr))return hr;

			// マウスの軸モードを設定
			DIPROPDWORD diprop = {};
			diprop.diph.dwSize = sizeof(diprop);
			diprop.diph.dwHeaderSize = sizeof(diprop.diph);
			diprop.diph.dwObj = 0;
			diprop.diph.dwHow = DIPH_DEVICE;
			diprop.dwData = DIPROPAXISMODE_REL; // 相対値モード
			hr = m_Mouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);

			hr = m_Mouse->Acquire();
			//if (FAILED(hr))return hr;
		}
		//{
		//	// ゲームパッドの初期化
		//	for (uint8_t i = 0; i < MAX_CONTROLLERS; i++) {
		//		hr = m_DirectInput->CreateDevice(GUID_Joystick, m_Gamepad->ReleaseAndGetAddressOf(), nullptr);
		//		if (FAILED(hr))return hr;
		//		hr = m_Keyboard->SetDataFormat(&c_dfDIJoystick);
		//		if (FAILED(hr))return hr;
		//		hr = m_Keyboard->SetCooperativeLevel(*pHWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		//		if (FAILED(hr))return hr;
		//		hr = m_Keyboard->Acquire();
		//		if (FAILED(hr))return hr;
		//	}
		//}

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
		// 失敗したら再接続を試みる
		if (FAILED(hr)) {
			hr = m_Keyboard->Acquire();
			if (SUCCEEDED(hr))
			{
				m_Keyboard->GetDeviceState(KEY_NUM, m_KeyState[m_NowSlot]);
			}
		}

		// マウスの状態を取得
		hr = m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState[m_NowSlot]);
		// 失敗したら再接続を試みる
		if (FAILED(hr)) {
			hr = m_Mouse->Acquire();
			if (SUCCEEDED(hr))
			{
				m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState[m_NowSlot]);
			}
		}
		else {
			// マウスのボタン情報をキー配列に移す
			for (uint8_t i = 0; i < BUTTON_EXPANSION; i++) {
				m_KeyState[m_NowSlot][KEY_NUM + i] = m_MouseState[m_NowSlot].rgbButtons[i];
			}
		}

		//// ゲームパッドの状態を取得
		//for (uint8_t i = 0; i < MAX_CONTROLLERS; i++) {
		//	hr = m_Gamepad[i]->GetDeviceState(sizeof(DIJOYSTATE), &m_GamepadState[i][m_NowSlot]);
		//	// 失敗したら再接続を試みる
		//	if (FAILED(hr)) {
		//		hr = m_Gamepad[i]->Acquire();
		//		if (hr == DIERR_INPUTLOST) {
		//			m_Gamepad[i]->Acquire();
		//		}
		//	}
		//}
	}

	//---------------------------------------------------------------------------------------------
	bool InputManager::IsKeyPressed(int id) const
	{
		return ((m_KeyState[m_NowSlot][id] & 0x80) == 0x80);
	}

	//---------------------------------------------------------------------------------------------
	bool InputManager::IsKeyReleased(int id) const
	{
		return ((m_KeyState[m_NowSlot][id] & 0x80) == 0x00);
	}

	//---------------------------------------------------------------------------------------------
	bool InputManager::IsKeyNowPressed(int id) const
	{
		return ((m_KeyState[m_NowSlot][id] & 0x80) == 0x80) &&
			((m_KeyState[!m_NowSlot][id] & 0x80) == 0x00);
	}

	//---------------------------------------------------------------------------------------------
	bool InputManager::IsKeyNowReleased(int id) const
	{
		return ((m_KeyState[m_NowSlot][id] & 0x80) == 0x00) &&
			((m_KeyState[!m_NowSlot][id] & 0x80) == 0x80);
	}

	//---------------------------------------------------------------------------------------------
	POINT InputManager::GetMouseMove() const
	{
		POINT ret;
		ret.x = m_MouseState[m_NowSlot].lX;
		ret.y = m_MouseState[m_NowSlot].lY;
		return ret;
	}

	//---------------------------------------------------------------------------------------------
	LONG InputManager::GetWheelDelta() const
	{
		return m_MouseState[m_NowSlot].lZ;
	}

	//---------------------------------------------------------------------------------------------
	void InputManager::SetShowCursor(BOOL show)
	{
		int cnt = ShowCursor(show);
		if (cnt >= 0)m_IsCursorShown = TRUE;
		else m_IsCursorShown = FALSE;
	}

	//---------------------------------------------------------------------------------------------
	void InputManager::SetCursorCenter()
	{
		auto myGame(&AK_Base::BaseWindow::GetInstance());
		auto windowSize = myGame->GetWindowSize();
		// ウィンドウの中央座標を計算
		POINT pos = { windowSize.x >> 1, windowSize.y >> 1 };
		// スクリーンに合わせる
		ClientToScreen(*(myGame->GetHWnd()), &pos);

		// カーソルをセット
		SetCursorPos(pos.x, pos.y);
	}

	//---------------------------------------------------------------------------------------------
	void InputManager::SetCursorPosition(int x, int y)
	{
		POINT pos({ x, y });
		SetCursorPosition(pos);
	}
	//---------------------------------------------------------------------------------------------
	void InputManager::SetCursorPosition(POINT& pos)
	{
		auto myGame(&AK_Base::BaseWindow::GetInstance());
		// スクリーンに合わせる
		ClientToScreen(*(myGame->GetHWnd()), &pos);

		// カーソルをセット
		SetCursorPos(pos.x, pos.y);
	}

	//---------------------------------------------------------------------------------------------
	POINT InputManager::GetCursorPosition() const
	{
		auto myGame(&AK_Base::BaseWindow::GetInstance());

		POINT point;
		// カーソル位置を取得
		if (GetCursorPos(&point)) {
			// ウィンドウ上の座標に合わせる
			if (ScreenToClient(*(myGame->GetHWnd()), &point)) {
				// 正常に取得できたら返す
				return point;
			}
		}

		point.x = -1;
		point.y = -1;
		return point;
	}

	//---------------------------------------------------------------------------------------------
	bool InputManager::IsGamepadPressed(uint8_t index, int id) const
	{
		return ((m_GamepadState[index][m_NowSlot].rgbButtons[id] & 0x80) == 0x80);
	}

	//---------------------------------------------------------------------------------------------
	bool InputManager::IsGamepadReleased(uint8_t index, int id) const
	{
		return ((m_GamepadState[index][m_NowSlot].rgbButtons[id] & 0x80) == 0x00);
	}

	//---------------------------------------------------------------------------------------------
	bool InputManager::IsGamepadNowPressed(uint8_t index, int id) const
	{
		return ((m_GamepadState[index][m_NowSlot].rgbButtons[id] & 0x80) == 0x80) &&
			((m_GamepadState[index][!m_NowSlot].rgbButtons[id] & 0x80) == 0x00);
	}

	//---------------------------------------------------------------------------------------------
	bool InputManager::IsGamepadNowReleased(uint8_t index, int id) const
	{
		return ((m_GamepadState[index][m_NowSlot].rgbButtons[id] & 0x80) == 0x00) &&
			((m_GamepadState[index][!m_NowSlot].rgbButtons[id] & 0x80) == 0x80);
	}

	//---------------------------------------------------------------------------------------------
	BOOL InputManager::CursorClipByWindow(BOOL s)
	{
		// ON
		if (s) {
			auto hwnd = BaseWindow::GetInstance().GetHWnd();

			// 左上座標
			POINT pos = { 0,0 };
			ClientToScreen(*hwnd, &pos);

			// 幅と高さを取得
			RECT window = {};
			GetClientRect(*hwnd, &window);

			// ウィンドウのクライアント領域の相対座標
			RECT rc = { pos.x, pos.y, pos.x + window.right, pos.y + window.bottom };
			BOOL r = ClipCursor(&rc);
			if (r) m_IsCursorClippedByWindow = TRUE;
			return r;
		}
		// OFF
		else {
			BOOL r = ClipCursor(nullptr);
			if (r) m_IsCursorClippedByWindow = FALSE;
			return r;
		}
	}
}