#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���x���ؗp�V�[��
// 
// �����	: amateurK
// �쐬��	: 2024/12/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Scene.h"
#include "Base/Tools/StepTimer.h"

namespace Scene {
	class FastCheck : public Scene
	{
	private:
		/// @brief ���Ԍo�߂��Ǘ�����X�e�b�v�^�C�}�[
		DX::StepTimer m_StepTimer;


	public:
		/// @brief �R���X�g���N�^
		FastCheck();
		/// @brief �f�X�g���N�^
		virtual ~FastCheck();

		/// @brief �V�[���̍X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Update()����̌o�ߎ��ԁi�b�j
		virtual void Update(const double& totalTime, const float& elapsedTime) override;


	};
}