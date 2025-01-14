
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
		LONG m_Width;
		/// @brief 縦幅
		LONG m_Height;
		/// @brief シェーダーリソースビュー
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_D3DShaderResourceView;

		/// @brief 画像が読み込まれているか
		bool m_IsVaild;

	public:
		/// @brief コンストラクタ
		PictureResource();
		/// @brief デストラクタ
		~PictureResource();

		/// @brief 画像をロードする（File）
		/// @param filename 画像へのパス
		/// @return ロードできたか
		virtual HRESULT LoadPicture(const std::wstring& filename);

		/// @brief 画像をロードする（Memory）
		/// @param imageData 画像のバイトデータ
		/// @param imageSize imageDataのサイズ
		/// @param size 画像のサイズ
		/// @return ロードできたか
		virtual HRESULT LoadPicture(const uint8_t* imageData, size_t imageSize);

		/// @brief 画像をロードする（バイナリデータ）
		/// @param imageData 画像のバイトデータ
		/// @param imageSize imageDataのサイズ
		/// @param size 画像のサイズ
		/// @param color 色数
		/// @return ロードできたか
		/// @details bmpファイルのような形式で来るので、自作ローダで処理している
		virtual HRESULT LoadPicture(const uint8_t* imageData,  const POINT& size, int color = 4);

		// ゲッター
		ID3D11ShaderResourceView** GetD3DSRView() { return m_D3DShaderResourceView.GetAddressOf(); }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
	};

}