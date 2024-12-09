#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���ʂ̒��_�V�F�[�_�[
// 
// �����	: amateurK
// �쐬��	: 2024/12/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "VertexShader.h"

namespace Shader {

	/// @brief ���ʂ̒��_�V�F�[�_�[
	__declspec(align(16))
		class BasicVS : public VertexShader
	{
	public:
		/// @brief ���t���[���ύX����鐔�l
		struct ChangesFrame
		{
			/// @brief 3�̍s���S���|�����킹������
			XMMATRIX MatrixWVP;
		};

		/// @brief �}�e���A���Ɋւ��鐔�l
		struct Material
		{
			/// @brief ��Z����F
			XMFLOAT4 Color;
		};

	public:
		/// @brief �R���X�g���N�^
		BasicVS();
		/// @brief �f�X�g���N�^
		virtual ~BasicVS();


		/// @brief ������
		/// @param params �g�p����p�����[�^�̍\����
		/// @return ����������
		virtual HRESULT Init(const ShaderInitParam& params) override;

		/// @brief ChageFrame�R���X�^���g�o�b�t�@���X�V
		/// @param world World�s��
		/// @details �ǉ����������邽�߁ASetConstantBuffer���g��Ȃ��ł�������g��
		void SetChangeFrame(const XMMATRIX& world);
	};
}
