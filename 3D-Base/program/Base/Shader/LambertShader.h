#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert�V�F�[�_�[�N���X
// 
// �����	: amateurK
// �쐬��	: 2024/08/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Shader.h"

namespace Shader {

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


	/// @brief �A�Ȃǂ��Ȃ���{�I�ȃV�F�[�_�[
	__declspec(align(16))
		class LambertShader
		: public Shader
	{
	private:

		/// @brief ���t���[���ύX����鐔�l���i�[����Ă���R���X�^���g�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_ChangesFrame;
		/// @brief �}�e���A���Ɋւ��鐔�l���i�[����Ă���R���X�^���g�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Material;
		/// @brief ���̋����Ɋւ��鐔�l���i�[����Ă���R���X�^���g�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Light;

	public:
		/// @brief �R���X�g���N�^
		LambertShader();
		/// @brief �f�X�g���N�^
		virtual ~LambertShader();


		/// @brief �����_�����O�̏���
		virtual void SetRendering() override;

		/// @brief ChangeFrame�R���X�^���g�o�b�t�@���X�V
		/// @param lightDirection ���̈ʒu�i���[���h���W�j
		void SetChangesFrame(const XMVECTOR& lightDirection);

		/// @brief Material�R���X�^���g�o�b�t�@���X�V
		/// @param materialAmbient �����̔��ˌW��
		/// @param materialDiffuse �g�U���ˌ��̔��ˌW��
		void SetMaterial(const XMFLOAT4& materialAmbient, const XMFLOAT4& materialDiffuse);
		
		/// @brief Light�R���X�^���g�o�b�t�@���X�V
		/// @param lightAmbient �����̋���
		/// @param lightDiffuse ���ˌ��̋���
		void SetLight(const XMFLOAT4& lightAmbient, const XMFLOAT4& lightDiffuse);


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(LambertShader));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}

	private:
		/// @brief �V�F�[�_�[���쐬
		/// @return ����������
		/// @details �V�F�[�_�[�̃R���p�C����ݒ�Ȃǂ��s���B��������̂ł킯������
		virtual HRESULT Create() override;

	};
}