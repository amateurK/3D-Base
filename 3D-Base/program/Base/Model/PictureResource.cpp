
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
		m_IsVaild = false;

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
		m_Width = static_cast<int>(meta.width);
		m_Height = static_cast<int>(meta.height);

		// ����ɓǂݍ��߂���摜��L����
		m_IsVaild = true;

		return hr;
	}

	//--------------------------------------------------------------------------------------
	HRESULT PictureResource::LoadPicture(const uint8_t* imageData, size_t imageSize)
	{
		HRESULT hr = S_OK;
		m_IsVaild = false;

		// BaseWindow����K�v�ȏ��𔲂��o��
		BaseWindow& bw(BaseWindow::GetInstance());
		auto device = bw.GetD3DDevice();

		// �摜�̏����擾���邽�߂̍\����
		TexMetadata meta = {};
		ScratchImage scratch = {};

		hr = DirectX::LoadFromWICMemory(imageData, imageSize, DirectX::WIC_FLAGS_NONE, nullptr, scratch);
		if (FAILED(hr))return hr;

		// �V�F�[�_�[���\�[�X�r���[���쐬
		hr = CreateShaderResourceViewEx(
			device, scratch.GetImage(0, 0, 0), scratch.GetImageCount(), meta,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			CREATETEX_DEFAULT, m_D3DShaderResourceView.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr))return hr;

		// �T�C�Y���擾
		m_Width = static_cast<int>(meta.width);
		m_Height = static_cast<int>(meta.height);

		// ����ɓǂݍ��߂���摜��L����
		m_IsVaild = true;

		return hr;
	}

	//--------------------------------------------------------------------------------------
	HRESULT PictureResource::LoadPicture(const uint8_t* imageData, const POINT& size, int color)
	{
		HRESULT hr = S_OK;
		m_IsVaild = false;

		m_Width = size.x;
		m_Height = size.y;

		// BaseWindow����K�v�ȏ��𔲂��o��
		BaseWindow& bw(BaseWindow::GetInstance());
		auto device = bw.GetD3DDevice();
		auto context = bw.GetImmediateContext();
		
		// �e�N�X�`���̍쐬
		Microsoft::WRL::ComPtr<ID3D11Texture2D> D3DTexture;
		D3D11_TEXTURE2D_DESC td;
		td.Width = m_Width;
		td.Height = m_Height;
		td.MipLevels = 1;
		td.ArraySize = 1;
		td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		td.SampleDesc.Count = 1;
		td.SampleDesc.Quality = 0;
		td.Usage = D3D11_USAGE_DYNAMIC;
		td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		td.MiscFlags = 0;
		hr = device->CreateTexture2D(&td, nullptr, &D3DTexture);
		if (FAILED(hr)) {
			return hr;
		}

		// �e�N�X�`�������ւ�
		D3D11_MAPPED_SUBRESOURCE msr;
		context->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		// msr��ł̕��imsr�̕���32�̔{���Ɋۂ߂���̂Łj
		int width32 = msr.RowPitch;

		// �f�[�^������������
		int widthx4 = m_Width * 4;
		for (int i = 0; i < m_Height; i++) {
			for (int j = 0; j < widthx4; j++) {
				memcpy((char*)(msr.pData) + i * width32 + j, imageData + (i * widthx4 + j), 1);
			}
		}

		context->Unmap(D3DTexture.Get(), 0);

		//�V�F�[�_���\�[�X�r���[�̍쐬
		D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
		srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srv.Texture2D.MipLevels = 1;
		hr = device->CreateShaderResourceView(D3DTexture.Get(), &srv, &m_D3DShaderResourceView);
		if (FAILED(hr)) {
			return hr;
		}

		return S_OK;
	}

}