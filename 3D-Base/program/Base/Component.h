
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �R���|�[�l���g
// Actor�Ɏ��t���Ďg��
// 
// �����	: amateurK
// �쐬��	: 2024/11/16
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#pragma once


namespace AK_Base { class Actor; }

namespace Component {

	/// @brief �R���|�[�l���g
	class Component
	{
	public:

		/// @brief �R���X�g���N�^
		Component();
		/// @brief �f�X�g���N�^
		virtual ~Component();

		/// @brief ���̃R���|�[�l���g�����L���Ă���Actor
		AK_Base::Actor* m_Parent;

		/// @brief �R���|�[�l���g�쐬���ɌĂяo�����֐�
		virtual void Setup();

		/// @brief �X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Move()����̌o�ߎ��ԁi�b�j
		virtual void Move(const double& totalTime, const float& elapsedTime);

		/// @brief �`��
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Render()����̌o�ߎ��ԁi�b�j
		virtual void Render(const double& totalTime, const float& elapsedTime);
	};

}