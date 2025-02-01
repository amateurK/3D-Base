#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �e�X�g�p�N���X
// 
// �����	: amateurK
// �쐬��	: 2024/04/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Scene.h"
#include "Base/Component/Camera.h"

namespace Scene {
	class TestScene : public Scene
	{
	private:

		/// @brief �J�����N���X
		AK_Base::Camera* m_Camera;

	public:
		/// @brief �R���X�g���N�^
		TestScene(std::wstring name = L"unnamed");
		/// @brief �f�X�g���N�^
		virtual ~TestScene();

		/// @brief �V�[���̍X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Update()����̌o�ߎ��ԁi�b�j
		virtual void Update(const double& totalTime, const float& elapsedTime) override;


	};
}