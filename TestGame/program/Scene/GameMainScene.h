#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Q�[���̃��C���V�[���̃N���X
// 
// �����	: amateurK
// �쐬��	: 2024/12/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Scene.h"
#include "Base/Camera/Camera.h"

namespace Scene {
	class GameMainScene : public Scene
	{
	private:

		/// @brief �J�����N���X
		std::unique_ptr<Camera::Camera> m_Camera;

	public:
		/// @brief �R���X�g���N�^
		GameMainScene();
		/// @brief �f�X�g���N�^
		virtual ~GameMainScene();

		/// @brief �V�[���̍X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Update()����̌o�ߎ��ԁi�b�j
		virtual void Update(const double& totalTime, const float& elapsedTime) override;


	};
}
