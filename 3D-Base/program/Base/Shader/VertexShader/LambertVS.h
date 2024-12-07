#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert���_�V�F�[�_�[
// 
// �����	: amateurK
// �쐬��	: 2024/12/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "VertexShader.h"

namespace Shader {

	/// @brief �R���X�^���g�o�b�t�@
	namespace {

		/// @brief ���t���[���ύX����鐔�l
		struct ChangesFrame
		{
			/// @brief 3�̍s���S���|�����킹������
			XMMATRIX MatrixWVP;
			/// @brief ���̃x�N�g���i���[�J�����W�n�j
			XMVECTOR LightDirection;
		};

		/// @brief �}�e���A���Ɋւ��鐔�l
		struct Material
		{
			/// @brief �����̔��ˌW���i���˗��A���̂̐F�A�A���x�h�j
			XMFLOAT4 MaterialAmbient;
			/// @brief �g�U���ˌ��̔��ˌW���i���˗��A���̂̐F�A�A���x�h�j
			XMFLOAT4 MaterialDiffuse;
		};

		/// @brief ���̋����Ɋւ��鐔�l
		struct Light
		{
			/// @brief �����̋���
			XMFLOAT4 LightAmbient;
			/// @brief ���ˌ��̋���
			XMFLOAT4 LightDiffuse;
		};

	}

	/// @brief Lambert���_�V�F�[�_�[
	__declspec(align(16))
		class LambertVS : public VertexShader
	{
	public:
		/// @brief �R���X�g���N�^
		LambertVS();
		/// @brief �f�X�g���N�^
		virtual ~LambertVS();

		
		/// @brief ������
		/// @param params �g�p����p�����[�^�̍\����
		/// @return ����������
		virtual HRESULT Init(const ShaderInitParam& params) override;

		/// @brief ChageFrame�R���X�^���g�o�b�t�@���X�V
		/// @param world World�s��
		/// @param light ���̍s��i���[���h���W�n�j
		/// @details �ǉ����������邽�߁ASetConstantBuffer���g��Ȃ��ł�������g��
		void SetChangeFrame(const XMMATRIX& world, const XMVECTOR& light);
	};
}
