#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �s�N�Z���V�F�[�_�[�̊��N���X
// 
// 
// �����	: amateurK
// �쐬��	: 2024/12/04
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../ShaderBase.h"

namespace Shader {

	/// @brief �s�N�Z���V�F�[�_�[�̊��N���X
	__declspec(align(16))
		class PixelShader : public ShaderBase
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

	public:
		/// @brief �R���X�g���N�^
		PixelShader();
		/// @brief �f�X�g���N�^
		virtual ~PixelShader();

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
