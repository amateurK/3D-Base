
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 画像データを持つクラス
// 1クラスにつき1枚のShaderResourceViewを持つ
// 
// 画像の読み込みはDirectXTexを使用
// 必要部分のみを抜き出して使用（pch.hにてinclude済み）
// https://github.com/Microsoft/DirectXTex
// 
// 製作者	: amateurK
// 作成日	: 2024/10/31
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#pragma once

namespace AK_Base {
	
	/// @brief 画像データを持つクラス
	class PictureResource
	{
	protected:
		/// @brief 横幅
		int m_Width;
		/// @brief 縦幅
		int m_Height;
		/// @brief シェーダーリソースビュー
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_D3DShaderResourceView;

		/// @brief 画像が読み込まれているか
		bool m_IsVaild;

	public:
		/// @brief コンストラクタ
		PictureResource();
		/// @brief デストラクタ
		~PictureResource();

		/// @brief 画像をロードする
		/// @param filename 画像へのパス
		/// @return ロードできたか
		virtual HRESULT LoadPicture(const std::wstring& filename);

		// ゲッター
		ID3D11ShaderResourceView** GetD3DSRView() { return m_D3DShaderResourceView.GetAddressOf(); }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
	};

}