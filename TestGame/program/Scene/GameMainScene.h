#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Q�[���̃��C���V�[���̃N���X
// 
// �����	: amateurK
// �쐬��	: 2024/12/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Scene.h"
#include "Base/Component/Camera.h"

namespace Scene {
	class GameMainScene : public Scene
	{
	private:

		/// @brief �J�����N���X
		AK_Base::Camera* m_Camera;

		// �v���C���[�̃A�N�^�[
		AK_Base::Actor* m_Player;

	public:
		/// @brief �R���X�g���N�^
		GameMainScene(std::wstring name = L"unnamed");
		/// @brief �f�X�g���N�^
		virtual ~GameMainScene();

		/// @brief �V�[���̍X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Update()����̌o�ߎ��ԁi�b�j
		virtual void Update(const double& totalTime, const float& elapsedTime) override;


	};
}
