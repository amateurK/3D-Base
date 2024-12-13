#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 入力管理クラス
// 
// 
// 製作者	: amateurK
// 作成日	: 2024/11/21
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// ボタンのコードの追加
// DIの定数がdefineで作られているので、色を合わせるためにdefineで作成
#define BUTTON_MOUSE0               0x100
#define BUTTON_MOUSE1               0x101
#define BUTTON_MOUSE2               0x102
#define BUTTON_MOUSE3               0x103
#define BUTTON_MOUSE4               0x104
#define BUTTON_MOUSE5               0x105
#define BUTTON_MOUSE6               0x106
#define BUTTON_MOUSE7               0x107

namespace AK_Base {

	namespace {
		/// @brief DirectInputに送るキーボードのキーの数（原則256）
		constexpr uint16_t KEY_NUM = 256;
		/// @brief 追加で処理するボタンの数
		constexpr uint16_t BUTTON_EXPANSION = 8;
		/// @brief ボタンの数
		constexpr uint16_t BUTTON_NUM = KEY_NUM + BUTTON_EXPANSION;
		/// @brief コントローラーの最大接続数
		constexpr uint8_t MAX_CONTROLLERS = 4;
	}

	/// @brief 入力管理クラス
	class InputManager
	{
	private:
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


	private:

		// 現在のキー状態を示す配列のインデックス
		bool m_NowSlot;
		/// @brief DirectInputのオブジェクト
		Microsoft::WRL::ComPtr<IDirectInput8> m_DirectInput;


		/// @brief 現在のキー状態
		BYTE m_KeyState[2][BUTTON_NUM];
		/// @brief キーボードデバイス
		Microsoft::WRL::ComPtr<IDirectInputDevice8> m_Keyboard;

		/// @brief 現在のマウスの状態
		DIMOUSESTATE m_MouseState[2];
		/// @brief マウスデバイス
		Microsoft::WRL::ComPtr<IDirectInputDevice8> m_Mouse;

		/// @brief 現在のゲームパッドの状態
		DIJOYSTATE m_GamepadState[MAX_CONTROLLERS][2];
		/// @brief ゲームパッドデバイス
		Microsoft::WRL::ComPtr<IDirectInputDevice8> m_Gamepad[MAX_CONTROLLERS];



		/// @brief カーソルが表示状態か
		BOOL m_IsCursorShown;
		/// @brief カーソルがウィンドウにクリップされているか
		BOOL m_IsCursorClippedByWindow;

	public:
		/// @brief 初期化
		/// @return 初期化が成功したか
		HRESULT Init();

		/// @brief キー状態を更新
		void Update();

		/// @brief キーが押されているか
		bool IsKeyPressed(int id) const;
		/// @brief キーが離されているか
		bool IsKeyReleased(int id) const;
		/// @brief キーが今押されたか
		bool IsKeyNowPressed(int id) const;
		/// @brief キーが今離されたか
		bool IsKeyNowReleased(int id) const;

		/// @brief マウスの移動量を取得
		/// @note マウスの移動量とカーソルの移動量が同じではないことに注意
		POINT GetMouseMove() const;
		/// @brief マウスホイールの移動量
		LONG GetWheelDelta() const;


		/// @brief マウスカーソルを表示切り替え
		/// @param show TRUEで表示、FALSEで非表示
		void SetShowCursor(BOOL show);
		/// @brief マウスカーソルを画面外にでないようにする
		/// @param s TRUEでON、FALSEでOFF
		/// @return 成功するとTRUE
		BOOL CursorClipByWindow(BOOL s);

		/// @brief マウスカーソルをウィンドウの中央に移動する
		void SetCursorCenter();
		/// @brief マウスカーソルをウィンドウの指定した場所に異動させる
		/// @param x 左上を0としたときのx座標
		/// @param y 左上を0としたときのy座標
		void SetCursorPosition(int x, int y);
		/// @brief マウスカーソルをウィンドウの指定した場所に異動させる
		/// @param x 左上を0としたときの座標
		void SetCursorPosition(POINT& pos);

		/// @brief ｋ－ソルの座標を取得
		/// @return POINT型
		POINT GetCursorPosition() const;


		/// @brief ゲームパッドのボタンが押されているか
		bool IsGamepadPressed(uint8_t index, int id) const;
		/// @brief ゲームパッドのボタンが離されているか
		bool IsGamepadReleased(uint8_t index, int id) const;
		/// @brief ゲームパッドのボタンが今押されたか
		bool IsGamepadNowPressed(uint8_t index, int id) const;
		/// @brief ゲームパッドのボタンが今離されたか
		bool IsGamepadNowReleased(uint8_t index, int id) const;

		// ゲッター

		inline BOOL GetIsCursorShown() const { return m_IsCursorShown; }
		inline BOOL GetIsCursorClippedByWindow() const { return m_IsCursorClippedByWindow; }
	};
}