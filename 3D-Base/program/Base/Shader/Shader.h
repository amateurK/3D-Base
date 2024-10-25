#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �V�F�[�_�[�N���X
// ���ۃN���X
// 
// �����	: amateurK
// �쐬��	: 2024/08/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


namespace Shader {

	/// @brief �V�F�[�_�[
	__declspec(align(16))
		class Shader
	{
	protected:
		ID3D11Device* m_D3DDevice;
		ID3D11DeviceContext* m_ImmediateContext;

		// unique_ptr����Class**�œn���Ƃ��ɖʓ|�Ȃ̂�ComPtr���g��

		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_VertexLayout;
		Microsoft::WRL::ComPtr<ID3D11BlendState> m_BlendState;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;

		DirectX::XMMATRIX m_World;
		DirectX::XMMATRIX m_View;
		DirectX::XMMATRIX m_Projection;

	public:
		/// @brief �R���X�g���N�^
		Shader();
		/// @brief �f�X�g���N�^
		virtual ~Shader();


		/// @brief �����_�����O�̏���
		virtual void SetRendering() = 0;


		/// @brief ���[���h�s����Z�b�g
		/// @param world ���[���h�s��
		inline void SetWorldMatrix(DirectX::XMMATRIX world)
		{
			m_World = world;
		}
		/// @brief �r���[�s����Z�b�g
		/// @param view �r���[�s��
		inline void SetViewMatrix(DirectX::XMMATRIX view)
		{
			m_View = view;
		}
		/// @brief �ˉe�s����Z�b�g
		/// @param projection �ˉe�s��
		inline void SetProjectionMatrix(DirectX::XMMATRIX projection)
		{
			m_Projection = projection;
		}


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Shader));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}

	private:
		/// @brief �V�F�[�_�[���쐬
		/// @return ����������
		/// @details �V�F�[�_�[�̃R���p�C����ݒ�Ȃǂ��s���B��������̂ł킯������
		virtual HRESULT Create() = 0;

	};
}