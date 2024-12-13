#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���͊Ǘ��N���X
// 
// 
// �����	: amateurK
// �쐬��	: 2024/11/21
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// �{�^���̃R�[�h�̒ǉ�
// DI�̒萔��define�ō���Ă���̂ŁA�F�����킹�邽�߂�define�ō쐬
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
		/// @brief DirectInput�ɑ���L�[�{�[�h�̃L�[�̐��i����256�j
		constexpr uint16_t KEY_NUM = 256;
		/// @brief �ǉ��ŏ�������{�^���̐�
		constexpr uint16_t BUTTON_EXPANSION = 8;
		/// @brief �{�^���̐�
		constexpr uint16_t BUTTON_NUM = KEY_NUM + BUTTON_EXPANSION;
		/// @brief �R���g���[���[�̍ő�ڑ���
		constexpr uint8_t MAX_CONTROLLERS = 4;
	}

	/// @brief ���͊Ǘ��N���X
	class InputManager
	{
	private:
		/// @brief �R���X�g���N�^
		InputManager();
		/// @brief �f�X�g���N�^
		~InputManager();

		static InputManager* Instance;
	public:
		InputManager(InputManager&&) = delete;
		InputManager& operator=(InputManager&&) = delete;

		InputManager(InputManager const&) = delete;
		InputManager& operator=(InputManager const&) = delete;

		/// @brief ���̃N���X�̃C���X�^���X���擾
		/// @return �C���X�^���X
		static InputManager* GetInstance() {
			return Instance;
		}
		/// @brief �C���X�^���X�𐶐�
		static void Create() {
			if (Instance == nullptr) {
				Instance = new InputManager;
			}
			else {
				throw std::exception("InputManager is a singleton");
			}
		}
		/// @brief �C���X�^���X�̉��
		static void Destroy() {
			delete Instance;
			Instance = nullptr;
		}


	private:

		// ���݂̃L�[��Ԃ������z��̃C���f�b�N�X
		bool m_NowSlot;
		/// @brief DirectInput�̃I�u�W�F�N�g
		Microsoft::WRL::ComPtr<IDirectInput8> m_DirectInput;


		/// @brief ���݂̃L�[���
		BYTE m_KeyState[2][BUTTON_NUM];
		/// @brief �L�[�{�[�h�f�o�C�X
		Microsoft::WRL::ComPtr<IDirectInputDevice8> m_Keyboard;

		/// @brief ���݂̃}�E�X�̏��
		DIMOUSESTATE m_MouseState[2];
		/// @brief �}�E�X�f�o�C�X
		Microsoft::WRL::ComPtr<IDirectInputDevice8> m_Mouse;

		/// @brief ���݂̃Q�[���p�b�h�̏��
		DIJOYSTATE m_GamepadState[MAX_CONTROLLERS][2];
		/// @brief �Q�[���p�b�h�f�o�C�X
		Microsoft::WRL::ComPtr<IDirectInputDevice8> m_Gamepad[MAX_CONTROLLERS];



		/// @brief �J�[�\�����\����Ԃ�
		BOOL m_IsCursorShown;
		/// @brief �J�[�\�����E�B���h�E�ɃN���b�v����Ă��邩
		BOOL m_IsCursorClippedByWindow;

	public:
		/// @brief ������
		/// @return ������������������
		HRESULT Init();

		/// @brief �L�[��Ԃ��X�V
		void Update();

		/// @brief �L�[��������Ă��邩
		bool IsKeyPressed(int id) const;
		/// @brief �L�[��������Ă��邩
		bool IsKeyReleased(int id) const;
		/// @brief �L�[���������ꂽ��
		bool IsKeyNowPressed(int id) const;
		/// @brief �L�[���������ꂽ��
		bool IsKeyNowReleased(int id) const;

		/// @brief �}�E�X�̈ړ��ʂ��擾
		/// @note �}�E�X�̈ړ��ʂƃJ�[�\���̈ړ��ʂ������ł͂Ȃ����Ƃɒ���
		POINT GetMouseMove() const;
		/// @brief �}�E�X�z�C�[���̈ړ���
		LONG GetWheelDelta() const;


		/// @brief �}�E�X�J�[�\����\���؂�ւ�
		/// @param show TRUE�ŕ\���AFALSE�Ŕ�\��
		void SetShowCursor(BOOL show);
		/// @brief �}�E�X�J�[�\������ʊO�ɂłȂ��悤�ɂ���
		/// @param s TRUE��ON�AFALSE��OFF
		/// @return ���������TRUE
		BOOL CursorClipByWindow(BOOL s);

		/// @brief �}�E�X�J�[�\�����E�B���h�E�̒����Ɉړ�����
		void SetCursorCenter();
		/// @brief �}�E�X�J�[�\�����E�B���h�E�̎w�肵���ꏊ�Ɉٓ�������
		/// @param x �����0�Ƃ����Ƃ���x���W
		/// @param y �����0�Ƃ����Ƃ���y���W
		void SetCursorPosition(int x, int y);
		/// @brief �}�E�X�J�[�\�����E�B���h�E�̎w�肵���ꏊ�Ɉٓ�������
		/// @param x �����0�Ƃ����Ƃ��̍��W
		void SetCursorPosition(POINT& pos);

		/// @brief ���|�\���̍��W���擾
		/// @return POINT�^
		POINT GetCursorPosition() const;


		/// @brief �Q�[���p�b�h�̃{�^����������Ă��邩
		bool IsGamepadPressed(uint8_t index, int id) const;
		/// @brief �Q�[���p�b�h�̃{�^����������Ă��邩
		bool IsGamepadReleased(uint8_t index, int id) const;
		/// @brief �Q�[���p�b�h�̃{�^�����������ꂽ��
		bool IsGamepadNowPressed(uint8_t index, int id) const;
		/// @brief �Q�[���p�b�h�̃{�^�����������ꂽ��
		bool IsGamepadNowReleased(uint8_t index, int id) const;

		// �Q�b�^�[

		inline BOOL GetIsCursorShown() const { return m_IsCursorShown; }
		inline BOOL GetIsCursorClippedByWindow() const { return m_IsCursorClippedByWindow; }
	};
}