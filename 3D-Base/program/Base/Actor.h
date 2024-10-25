#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Q�[�����̑S�ẴI�u�W�F�N�g���p������N���X
// �I�u�W�F�N�g��؍\���ŏ������邽�߂̂���
// 
// �����	: amateurK
// �쐬��	: 2024/03/21
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "BaseWindow.h"

namespace AK_Base {

	/// @brief Actor�̏�Ԃ�\��
	enum class ActorStatus {
		ACTION,		// �s����
		MOVEONLY,	// Move()�̂�
		RENDERONLY,	// Render()�̂�
		REST,		// �x�e��(�Ȃɂ����Ȃ�)
		DEAD,		// ���S = �������I�������폜�����
	};

	/// @brief �A�N�^�[�N���X
	class Actor
	{
	protected:
		ActorStatus m_Status;	// ���݂̏��
		std::wstring m_ActorName;	// Actor�̎��ʖ�

		std::list<Actor*> m_Children;	// �qActor�̃��X�g
		Actor* m_Parent;	// �eActor�ւ̃|�C���^

	public:
		/// @brief �R���X�g���N�^
		/// @param name : ���ʖ�
		/// @param status : �������
		Actor(
			std::wstring name = L"unnamed"
		);

		/// @brief �f�X�g���N�^
		virtual ~Actor();

		/// @brief �X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Move()����̌o�ߎ��ԁi�b�j
		virtual void Move(const double& totalTime, const float& elapsedTime);
		/// @brief �`��
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Render()����̌o�ߎ��ԁi�b�j
		virtual void Render(const double& totalTime, const float& elapsedTime);

		/// @brief �q�A�N�^�[�̒ǉ�
		/// @param actor : �ǉ�����q�A�N�^�[
		virtual void AddChild(Actor* const actor);
		/// @brief ���݂̏�Ԃ��m�F���āADEAD��ԂȂ�폜
		virtual void CheckStatus();

		/// @brief ACTIVE��Ԃ̎qActor�̐���Ԃ�
		/// @return �����ɍ����qActor�̐�
		int GetActionChildren() const;
		/// @brief DEAD��Ԃł͂Ȃ��qActor�̐���Ԃ�
		/// @return �����ɍ����qActor�̐�
		int GetAliveChildren() const;

		/// @brief �qActor�������̃N���X��T��
		/// @param type : �T�������N���X�itypeid()���g���j
		/// @param list : ���������N���X���i�[���邽�߂̃��X�g
		void SearchClass(const type_info& type, std::list<const Actor*>*& list) const;

		/// @brief �qActor�������̖��O��Actor��T��
		/// @param name : �T������Actor�̖��O
		/// @return ��������Actor�ւ̃|�C���^
		const Actor* SearchName(const std::wstring name) const;

		/// @brief ���݂̏�Ԃ�ύX
		/// @param status �ύX��������ԁiActorStatus�^�j
		void SetStatus(const ActorStatus status);

		/// @brief �e��Actor���Z�b�g
		/// @param actor �eActor�ւ̃|�C���^
		void SetParent(Actor* const actor);
	};
}
