#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 3D���f�����������I�u�W�F�N�g���p������N���X
// 
// �����	: amateurK
// �쐬��	: 2024/04/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Actor.h"
#include "ModelRender.h"

namespace AK_Base {

	/// @brief 3D���f�������A�N�^�[
	__declspec(align(16))
		class ModelActor : public Actor
	{
	protected:
		/// @brief 3D���f���̕`��Ǘ��N���X
		std::unique_ptr<ModelRender> m_ModelRender;

		/// @brief ���[���h�s��
		DirectX::XMMATRIX m_WorldMatrix;
		/// @brief ���ݍ��W
		DirectX::XMFLOAT3A m_Position;
		/// @brief ��]�p�x
		float m_Rotation;
		/// @brief �X�P�[��
		DirectX::XMFLOAT3A m_Scale;

		/// @brief �\�����邩
		/// @details true = �\��
		bool m_IsVisible;

	public:
		/// @brief �R���X�g���N�^
		/// @param shader �g�p����V�F�[�_�[�ւ̃|�C���^
		/// @param name ���ʖ�
		/// @param fileName �g�p���郁�b�V���̃t�@�C����
		ModelActor(
			Shader::Shader* const shader
			, std::wstring name = L"unnamed"
			, std::wstring fileName = L""
		);

		/// @brief �f�X�g���N�^
		virtual ~ModelActor();

		
		/// @brief �X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Move()����̌o�ߎ��ԁi�b�j
		virtual void Move(const double& totalTime, const float& elapsedTime) override;
		/// @brief �`��
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Render()����̌o�ߎ��ԁi�b�j
		virtual void Render(const double& totalTime, const float& elapsedTime) override;

		/// @brief ���[���h�s����X�V����
		/// @details �I�[�o�[���C�h�����z��
		virtual void CalcWorldMatrix();
		

		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(ModelActor));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}