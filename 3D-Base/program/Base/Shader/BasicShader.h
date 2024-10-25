#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �A�Ȃǂ��Ȃ���{�I�ȃV�F�[�_�[
// 
// �����	: amateurK
// �쐬��	: 2024/04/20
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Shader.h"

namespace Shader {

	struct ChangesFrame
	{
		/// @brief 3�̍s���S���|�����킹������
		XMMATRIX matrixWVP;
	};

	/// @brief �A�Ȃǂ��Ȃ���{�I�ȃV�F�[�_�[
	__declspec(align(16))
	class BasicShader
		: public Shader
	{
	private:

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_ChangesFrame;

	public:
		/// @brief �R���X�g���N�^
		BasicShader();
		/// @brief �f�X�g���N�^
		virtual ~BasicShader();


		/// @brief �����_�����O�̏���
		virtual void SetRendering() override;


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(BasicShader));
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