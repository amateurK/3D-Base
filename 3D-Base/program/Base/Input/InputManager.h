#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 入力管理クラス
// 
// 
// 製作者	: amateurK
// 作成日	: 2024/11/21
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )


namespace AK_Base {

	namespace {
		constexpr uint16_t KEY_NUM = 256;
	}

	/// @brief 入力管理クラス
	class InputManager
	{
	private:

		/// @brief 現在のキー状態
		BYTE m_KeyState[2][KEY_NUM];

		// 現在のキー状態を示す配列のインデックス
		bool m_NowSlot;

		/// @brief DirectInputのオブジェクト
		Microsoft::WRL::ComPtr<IDirectInput8> m_DirectInput;
		/// @brief DirectInputのキーボードデバイス
		Microsoft::WRL::ComPtr<IDirectInputDevice8> m_Keyboard;

		/// @brief コンストラクタ
		InputManager();
		/// @brief デストラクタ
		~InputManager();

		static InputManager* Instance;
	public:
		InputManager(InputManager&&) = delete;
		InputManager& operator=(InputManager&&) = delete;

		InputManager(InputManager const&) = delete;
		InputManager& operator=(InputManager const&) = delete;

		/// @brief このクラスのインスタンスを取得
		/// @return インスタンス
		static InputManager* GetInstance() {
			return Instance;
		}
		/// @brief インスタンスを生成
		static void Create() {
			if (Instance == nullptr) {
				Instance = new InputManager;
			}
			else {
				throw std::exception("InputManager is a singleton");
			}
		}
		/// @brief インスタンスの解放
		static void Destroy() {
			delete Instance;
			Instance = nullptr;
		}

		/// @brief 初期化
		/// @return 初期化が成功したか
		HRESULT Init();

		/// @brief キー状態を更新
		void Update();

		/// @brief キーが押されているか
		bool IsKeyPressed(int id);
		/// @brief キーが離されているか
		bool IsKeyReleased(int id);
		/// @brief キーが今押されたか
		bool IsKeyNowPressed(int id);
		/// @brief キーが今離されたか
		bool IsKeyNowReleased(int id);
	};
}