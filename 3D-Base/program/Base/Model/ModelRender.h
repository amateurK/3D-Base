#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 3D���f���`��Ǘ��N���X
// 
// �����	: amateurK
// �쐬��	: 2024/04/12
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Shader/Shader.h"
#include "Mesh/Mesh.h"

namespace AK_Base {
	/// @brief 3D���f���`��Ǘ��N���X
	/// @details 3D���f���̊Ǘ���ModelActor�ƕʂŏ�������������
	class ModelRender
	{
	private:
		Shader::Shader* m_Shader;
		Mesh::Mesh* m_Mesh;

	public:
		/// @brief �R���X�g���N�^
		/// @param shader �g�p����V�F�[�_�[
		ModelRender(Shader::Shader* const shader);
		/// @brief �f�X�g���N�^
		virtual ~ModelRender();

		/// @brief ���\�[�X�̍쐬
		/// @return �쐬�ɐ���������
		HRESULT CreateResource(std::wstring fileName = L"__box");

		/// @brief �`��
		/// @param worldMatrix �`�悷��I�u�W�F�N�g�̃��[���h�s��
		void Render(const DirectX::XMMATRIX& worldMatrix);

	};
}