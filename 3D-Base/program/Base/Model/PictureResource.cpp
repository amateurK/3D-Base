
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �摜�f�[�^�����N���X
// 1�N���X�ɂ�1����ShaderResourceView������
// 
// directxtex_desktop_win10���g�p
// ������ FbxMesh.h �̂��̂Ɠ��l
// �ǉ��̃C���N���[�h�f�B���N�g��
// �@$(SolutionDir)packages\directxtex_desktop_win10.2024.10.29.1\include
// 
// �����	: amateurK
// �쐬��	: 2024/10/31
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "PictureResource.h"
#include "../BaseWindow.h"
#include <DirectXTex.h>

// �Ή�����lib�t�@�C����ǂݍ���
#if defined( DEBUG ) || defined( _DEBUG )
// Debug�p
#pragma comment(lib, "../packages/directxtex_desktop_win10.2024.10.29.1/native/lib/x64/Debug/DirectXTex.lib")
#else
// Release�p
#pragma comment(lib, "../packages/directxtex_desktop_win10.2024.10.29.1/native/lib/x64/Release/DirectXTex.lib")
#endif

namespace AK_Base {
	//--------------------------------------------------------------------------------------
	PictureResource::PictureResource()
		: m_Width(0)
		, m_Height(0)
		, m_IsVaild(false)
	{

	}
	//--------------------------------------------------------------------------------------
	PictureResource::~PictureResource()
	{

	}

	//--------------------------------------------------------------------------------------
	HRESULT PictureResource::LoadPicture(const std::wstring& filename)
	{
		HRESULT hr = S_OK;

		// BaseWindow����K�v�ȏ��𔲂��o��
		BaseWindow& bw(BaseWindow::GetInstance());
		auto device = bw.GetD3DDevice();

		// �摜�̏����擾���邽�߂̍\����
		TexMetadata meta = {};
		ScratchImage scratch = {};

		// �g���q�ʂɏ���
		auto extension = Tools::GetFileExtension(filename);
		if (extension == L"tga" || extension == L"TGA")
		{
			hr = LoadFromTGAFile(filename.c_str(), &meta, scratch);
		}
		else
		{
			hr = LoadFromWICFile(filename.c_str(), WIC_FLAGS_NONE, &meta, scratch);
		}
		if (FAILED(hr))return hr;

		// �V�F�[�_�[���\�[�X�r���[���쐬
		hr = CreateShaderResourceViewEx(
			device, scratch.GetImage(0, 0, 0), scratch.GetImageCount(), meta,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			CREATETEX_DEFAULT, m_D3DShaderResourceView.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr))return hr;

		// �T�C�Y���擾
		m_Width = meta.width;
		m_Height = meta.height;

		// ����ɓǂݍ��߂���摜��L����
		m_IsVaild = true;

		return hr;
	}

	////--------------------------------------------------------------------------------------
	//HRESULT PictureResource::LoadPicture(const std::wstring& filename)
	//{
	//	using namespace Microsoft::WRL;
	//	HRESULT hr = S_OK;
	//	m_IsVaild = false;


	//	// BaseWindow����K�v�ȏ��𔲂��o��
	//	BaseWindow& bw(BaseWindow::GetInstance());
	//	auto device = bw.GetD3DDevice();
	//	auto context = bw.GetImmediateContext();

	//	// �ڍׂȏ��̎擾�p
	//	ComPtr<ID3D11Resource> res;

	//	// DDS���𔻕ʂ��鏈���͍쐬���Ă��Ȃ�
	//	// DDS���g�����Ƃ��������ꍇ�͎�������\��...
	//	hr = DirectX::CreateWICTextureFromFileEx(
	//		device, context, filename.c_str(), 0,
	//		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE,
	//		0, 0, WIC_LOADER_DEFAULT,
	//		res.ReleaseAndGetAddressOf(),
	//		m_D3DShaderResourceView.ReleaseAndGetAddressOf()
	//	);
	//	if (FAILED(hr))return hr;

	//	// �ǂݍ��񂾉摜�̏����擾
	//	ComPtr<ID3D11Texture2D> tex;
	//	hr = res.As(&tex);
	//	if (FAILED(hr))return hr;
	//	D3D11_TEXTURE2D_DESC desc;
	//	tex->GetDesc(&desc);

	//	// �T�C�Y���擾
	//	m_Width = desc.Width;
	//	m_Height = desc.Height;

	//	// ����ɓǂݍ��߂���摜��L����
	//	m_IsVaild = true;

	//	return hr;
	//}
}