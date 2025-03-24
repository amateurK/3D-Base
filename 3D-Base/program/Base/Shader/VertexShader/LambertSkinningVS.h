#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert���_�V�F�[�_�[
// �X�L�j���O�A�j���[�V�������s��
// 
// �����	: amateurK
// �쐬��	: 2025/02/14
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "LambertVS.h"

namespace Shader {

	/// @brief Lambert���_�V�F�[�_�[
	__declspec(align(16))
		class LambertSkinningVS : public LambertVS
	{
	public:

		/// @brief �{�[���̍s��
		struct Bones
		{
			DirectX::XMMATRIX BoneMatrix[100];
		};

	public:
		/// @brief �R���X�g���N�^
		LambertSkinningVS();
		/// @brief �f�X�g���N�^
		virtual ~LambertSkinningVS();


		/// @brief ������
		/// @param params �g�p����p�����[�^�̍\����
		/// @return ����������
		virtual HRESULT Init(const ShaderInitParam& params) override;

		/// @brief �V�F�[�_�[��GPU�ɃZ�b�g����
		/// @param set ShaderSet�̃|�C���^
		virtual void SetShader(const ShaderSet* set) override;

		/// @brief �I�u�W�F�N�g���ƂɕύX�����l��GPU�ɃZ�b�g����
		/// @param set ShaderSet�̃|�C���^
		virtual void SetPerObject(const ShaderSet* set) override;

		/// @brief �V�F�[�_�[�Ŏg�p�����l��ShaderSet�ɒǉ�
		/// @param set ShaderSet�̃|�C���^
		virtual void AddDataForShaderSet(ShaderSet* set) const override;
	};
}
