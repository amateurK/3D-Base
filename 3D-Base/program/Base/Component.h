#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �R���|�[�l���g
// Actor�Ɏ��t���Ďg��
// 
// �����	: amateurK
// �쐬��	: 2024/11/16
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Actor.h"

namespace AK_Base {

	/// @brief �R���|�[�l���g
	class Component
	{
	private:

		/// @brief ���̃R���|�[�l���g�����L���Ă���Actor
		AK_Base::Actor* m_Parent;


	public:

		/// @brief �R���X�g���N�^
		Component()
		{
		}
		/// @brief �f�X�g���N�^
		virtual ~Component()
		{
		}

		/// @brief �R���|�[�l���g�̖��O���擾
		/// @return ���O�̕�����
		virtual std::string GetName() const = 0;


		/// @brief �X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Move()����̌o�ߎ��ԁi�b�j
		virtual void Move(const double& totalTime, const float& elapsedTime) {};

		/// @brief �`��
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Render()����̌o�ߎ��ԁi�b�j
		virtual void Render(const double& totalTime, const float& elapsedTime) {};

		/// @brief ���̃R���|�[�l���g�����L���Ă���Actor��Ԃ�
		/// @return Actor�̃|�C���^
		AK_Base::Actor* GetActor() const
		{
			return m_Parent;
		}
	};

}