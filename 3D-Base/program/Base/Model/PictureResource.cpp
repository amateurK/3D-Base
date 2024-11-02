
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
		m_Width = meta.width;
		m_Height = meta.height;

		// 正常に読み込めたら画像を有効化
		m_IsVaild = true;

		return hr;
	}

	////--------------------------------------------------------------------------------------
	//HRESULT PictureResource::LoadPicture(const std::wstring& filename)
	//{
	//	using namespace Microsoft::WRL;
	//	HRESULT hr = S_OK;
	//	m_IsVaild = false;


	//	// BaseWindowから必要な情報を抜き出し
	//	BaseWindow& bw(BaseWindow::GetInstance());
	//	auto device = bw.GetD3DDevice();
	//	auto context = bw.GetImmediateContext();

	//	// 詳細な情報の取得用
	//	ComPtr<ID3D11Resource> res;

	//	// DDSかを判別する処理は作成していない
	//	// DDSを使うことがあった場合は実装する予定...
	//	hr = DirectX::CreateWICTextureFromFileEx(
	//		device, context, filename.c_str(), 0,
	//		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE,
	//		0, 0, WIC_LOADER_DEFAULT,
	//		res.ReleaseAndGetAddressOf(),
	//		m_D3DShaderResourceView.ReleaseAndGetAddressOf()
	//	);
	//	if (FAILED(hr))return hr;

	//	// 読み込んだ画像の情報を取得
	//	ComPtr<ID3D11Texture2D> tex;
	//	hr = res.As(&tex);
	//	if (FAILED(hr))return hr;
	//	D3D11_TEXTURE2D_DESC desc;
	//	tex->GetDesc(&desc);

	//	// サイズを取得
	//	m_Width = desc.Width;
	//	m_Height = desc.Height;

	//	// 正常に読み込めたら画像を有効化
	//	m_IsVaild = true;

	//	return hr;
	//}
}