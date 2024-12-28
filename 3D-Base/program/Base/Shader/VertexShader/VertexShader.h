#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���_�V�F�[�_�[�̊��N���X
// 
// 
// �����	: amateurK
// �쐬��	: 2024/11/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../ShaderBase.h"

namespace Shader {

	/// @brief ���_�V�F�[�_�[������������ۂɎg�p����p�����[�^�[�Q
	struct VertexShaderInitParam
		: public ShaderInitParam {
		/// @brief ���_�V�F�[�_�[�ւ̓��̓��C�A�E�g
		const D3D11_INPUT_ELEMENT_DESC* Layout;
		/// @brief ���̓��C�A�E�g�̐�
		UINT LayoutCount;
	};

	/// @brief ���_�V�F�[�_�[�̊��N���X
	__declspec(align(16))
		class VertexShader : public ShaderBase
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;

	public:
		/// @brief �R���X�g���N�^
		VertexShader();
		/// @brief �f�X�g���N�^
		virtual ~VertexShader();

		/// @brief ������
		/// @param params �g�p����p�����[�^�̍\����
		/// @return ����������
		virtual HRESULT Init(const ShaderInitParam& params) override;

		/// @brief �V�F�[�_�[��GPU�ɃZ�b�g����
		/// @param set ShaderSet�̃|�C���^
		virtual void SetShader(const ShaderSet* set) override;

		/// @brief �R���X�^���g�o�b�t�@���o�C���h
		/// @param index �o�C���h����R���X�^���g�o�b�t�@�̃C���f�b�N�X
		virtual void UpdateGPUConstantBuffer(size_t index) override;

	};
}

