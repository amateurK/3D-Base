
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �摜�f�[�^�����N���X
// 1�N���X�ɂ�1����ShaderResourceView������
// 
// �摜�̓ǂݍ��݂�DirectXTex���g�p
// �K�v�����݂̂𔲂��o���Ďg�p�ipch.h�ɂ�include�ς݁j
// https://github.com/Microsoft/DirectXTex
// 
// �����	: amateurK
// �쐬��	: 2024/10/31
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#pragma once

namespace AK_Base {
	
	/// @brief �摜�f�[�^�����N���X
	class PictureResource
	{
	protected:
		/// @brief ����
		int m_Width;
		/// @brief �c��
		int m_Height;
		/// @brief �V�F�[�_�[���\�[�X�r���[
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_D3DShaderResourceView;

		/// @brief �摜���ǂݍ��܂�Ă��邩
		bool m_IsVaild;

	public:
		/// @brief �R���X�g���N�^
		PictureResource();
		/// @brief �f�X�g���N�^
		~PictureResource();

		/// @brief �摜�����[�h����
		/// @param filename �摜�ւ̃p�X
		/// @return ���[�h�ł�����
		virtual HRESULT LoadPicture(const std::wstring& filename);

		// �Q�b�^�[
		ID3D11ShaderResourceView** GetD3DSRView() { return m_D3DShaderResourceView.GetAddressOf(); }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
	};

}