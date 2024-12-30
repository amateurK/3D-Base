
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 画像データを持つクラス
// 1クラスにつき1枚のShaderResourceViewを持つ
// 
// directxtex_desktop_win10を使用
// 導入は FbxMesh.h のものと同様
// 追加のインクルードディレクトリ
// 　$(SolutionDir)packages\directxtex_desktop_win10.2024.10.29.1\include
// 
// 製作者	: amateurK
// 作成日	: 2024/10/31
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "PictureResource.h"
#include "../BaseWindow.h"
#include <DirectXTex.h>

// 対応するlibファイルを読み込み
#if defined( DEBUG ) || defined( _DEBUG )
// Debug用
#pragma comment(lib, "../packages/directxtex_desktop_win10.2024.10.29.1/native/lib/x64/Debug/DirectXTex.lib")
#else
// Release用
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

		// BaseWindowから必要な情報を抜き出し
		BaseWindow& bw(BaseWindow::GetInstance());
		auto device = bw.GetD3DDevice();

		// 画像の情報を取得するための構造体
		TexMetadata meta = {};
		ScratchImage scratch = {};

		// 拡張子別に処理
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

		// シェーダーリソースビューを作成
		hr = CreateShaderResourceViewEx(
			device, scratch.GetImage(0, 0, 0), scratch.GetImageCount(), meta,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			CREATETEX_DEFAULT, m_D3DShaderResourceView.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr))return hr;

		// サイズを取得
		m_Width = static_cast<int>(meta.width);
		m_Height = static_cast<int>(meta.height);

		// 正常に読み込めたら画像を有効化
		m_IsVaild = true;

		return hr;
	}

	//--------------------------------------------------------------------------------------
	HRESULT PictureResource::LoadPicture(const uint8_t* imageData, size_t imageSize)
	{
		HRESULT hr = S_OK;
		m_IsVaild = false;

		// BaseWindowから必要な情報を抜き出し
		BaseWindow& bw(BaseWindow::GetInstance());
		auto device = bw.GetD3DDevice();

		// 画像の情報を取得するための構造体
		TexMetadata meta = {};
		ScratchImage scratch = {};

		hr = DirectX::LoadFromWICMemory(imageData, imageSize, DirectX::WIC_FLAGS_NONE, nullptr, scratch);
		if (FAILED(hr))return hr;

		// シェーダーリソースビューを作成
		hr = CreateShaderResourceViewEx(
			device, scratch.GetImage(0, 0, 0), scratch.GetImageCount(), meta,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			CREATETEX_DEFAULT, m_D3DShaderResourceView.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr))return hr;

		// サイズを取得
		m_Width = static_cast<int>(meta.width);
		m_Height = static_cast<int>(meta.height);

		// 正常に読み込めたら画像を有効化
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

		// BaseWindowから必要な情報を抜き出し
		BaseWindow& bw(BaseWindow::GetInstance());
		auto device = bw.GetD3DDevice();
		auto context = bw.GetImmediateContext();
		
		// テクスチャの作成
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

		// テクスチャ書き替え
		D3D11_MAPPED_SUBRESOURCE msr;
		context->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		// msr上での幅（msrの幅は32の倍数に丸められるので）
		int width32 = msr.RowPitch;

		// データを書き換える
		int widthx4 = m_Width * 4;
		for (int i = 0; i < m_Height; i++) {
			for (int j = 0; j < widthx4; j++) {
				memcpy((char*)(msr.pData) + i * width32 + j, imageData + (i * widthx4 + j), 1);
			}
		}

		context->Unmap(D3DTexture.Get(), 0);

		//シェーダリソースビューの作成
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