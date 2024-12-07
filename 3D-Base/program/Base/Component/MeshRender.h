#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 3D���f����`�悷��R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2024/11/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"
#include "../Actor.h"
#include "Transform.h"

namespace Shader { class ShaderSet; }
namespace Mesh { class Mesh; }

namespace AK_Base {
	class Transform;

	__declspec(align(16))
		class MeshRender : public Component
	{
	private:

		/// @brief ����Actor��Transform�R���|�[�l���g
		Transform* m_Transform;

		/// @brief �g�p����V�F�[�_�[�̃|�C���^
		Shader::ShaderSet* m_ShaderSet;

		/// @brief �g�p���郁�b�V���̃|�C���^
		Mesh::Mesh* m_Mesh;

	public:
		/// @brief �R���X�g���N�^
		/// @param parent ���̃R���|�[�l���g�����L���Ă���Actor
		/// @param fileName �t�@�C����
		MeshRender(Actor* const parent, std::wstring fileName = L"__box");
		/// @brief �f�X�g���N�^
		virtual ~MeshRender() = default;

		/// @brief �R���|�[�l���g�̖��O���擾
		/// @return ���O�̕�����
		inline virtual std::string GetName() const override { return "MeshRender"; }

		/// @brief �`��
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Render()����̌o�ߎ��ԁi�b�j
		virtual void Render(const double& totalTime, const float& elapsedTime) override;

	private:

		/// @brief ���\�[�X�̍쐬
		/// @param fileName �t�@�C����
		/// @return �쐬�ɐ���������
		HRESULT CreateResource(std::wstring fileName = L"__box");
	};
}