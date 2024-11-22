#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���͊Ǘ��N���X
// 
// 
// �����	: amateurK
// �쐬��	: 2024/11/21
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//#include <dinput.h>

namespace AK_Base {

	/// @brief ���͊Ǘ��N���X
	class InputManager
	{
	private:

		/// @brief ���݂̃L�[���
		BYTE m_KeyState[2][256];

		// ���݂̃L�[��Ԃ������z��̃C���f�b�N�X
		bool m_NowSlot;

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

		/// @brief �L�[��Ԃ��X�V
		void Update();

		/// @brief �L�[��������Ă��邩
		bool IsKeyPressed(int id);
		/// @brief �L�[��������Ă��邩
		bool IsKeyReleased(int id);
		/// @brief �L�[���������ꂽ��
		bool IsKeyNowPressed(int id);
		/// @brief �L�[���������ꂽ��
		bool IsKeyNowReleased(int id);
	};
}