#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �V�[���N���X
// 
// �����	: amateurK
// �쐬��	: 2024/04/22
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Base/Actor.h"

namespace Scene {

	/// @brief �V�[���N���X
	class Scene :public AK_Base::Actor 
	{
	protected:
		/// @brief Move()�̎��s��
		uint32_t m_Times;

	public:
		/// @brief �R���X�g���N�^
		Scene();
		/// @brief �f�X�g���N�^
		virtual ~Scene();

		/// @brief �V�[���̍X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Move()����̌o�ߎ��ԁi�b�j
		virtual void Move(const double& totalTime, const float& elapsedTime) override;


		/// @brief ACTION��ԂɈڍs
		virtual void ChangeAction() {
			m_Status = AK_Base::ActorStatus::ACTION;
		}
		/// @brief REST��ԂɈȍ~
		virtual void ChangeRest() {
			m_Status = AK_Base::ActorStatus::REST;
		}
	};
}