#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �X�L�j���O�A�j���[�V����������3D���f����`�悷��R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2025/02/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"
#include "../Actor.h"
#include "Transform.h"

namespace Shader { class ShaderSet; }
namespace Mesh { 
	class SkinningMesh;
	struct BoneData;
}

namespace AK_Base {

	__declspec(align(16))
		class SkinningMeshRender : public Component
	{
	private:

		/// @brief �g�p����V�F�[�_�[�̃|�C���^
		Shader::ShaderSet* m_ShaderSet;

		/// @brief �g�p���郁�b�V���̃|�C���^
		Mesh::SkinningMesh* m_Mesh;

		/// @brief �{�[���̍s��
		std::vector<DirectX::XMMATRIX> m_BoneMatrices;

	public:
		/// @brief �R���X�g���N�^
		/// @param parent ���̃R���|�[�l���g�����L���Ă���Actor
		/// @param fileName �t�@�C����
		SkinningMeshRender(Actor* const parent, std::wstring fileName = L"__box");
		/// @brief �f�X�g���N�^
		virtual ~SkinningMeshRender() = default;

		/// @brief �R���|�[�l���g�̖��O���擾
		/// @return ���O�̕�����
		inline virtual std::string GetName() const override { return "SkinningMeshRender"; }

		/// @brief �`��
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Render()����̌o�ߎ��ԁi�b�j
		virtual void Render(const double& totalTime, const float& elapsedTime) override;

		/// @brief �g�p����V�F�[�_�[���Z�b�g
		/// @param name �V�F�[�_�[�Z�b�g�̖��O
		void SetShader(const std::string& name);


	private:

		/// @brief ���\�[�X�̍쐬
		/// @param fileName �t�@�C����
		/// @return �쐬�ɐ���������
		HRESULT CreateResource(std::wstring fileName = L"__box");

	};
}