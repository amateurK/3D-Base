#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// メッシュデータクラス
// 抽象クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/08/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../PictureResource.h" 

namespace Mesh {

	/// @brief インポート時のパラメータ
	struct ImportSettings
	{
		/// @brief U座標を反転させるか
		bool InverseU = false;
		/// @brief V座標を反転させるか
		bool InverseV = false;

		ImportSettings(bool invU = false, bool invV = false)
			: InverseU(invU)
			, InverseV(invV)
		{}
	};

	/// @brief マテリアルデータ
	struct MeshData
	{
		/// @brief このマテリアルを使用しているポリゴンの頂点バッファ
		Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
		/// @brief このマテリアルを使用しているポリゴンのインデックスバッファ
		Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer;
		/// @brief このマテリアルを使用している頂点の数
		uint32_t NumVertex;
		/// @brief このマテリアルを使用しているポリゴン数
		uint32_t NumFace;
		/// @brief 使用されているテクスチャのリソースビューへのポインタ
		ID3D11ShaderResourceView** SRView;
		/// @brief インデックスバッファの1データのサイズ
		DXGI_FORMAT DXGI_Format;

		/// @brief デストラクタ
		~MeshData() 
		{
			IndexBuffer.Reset();
			VertexBuffer.Reset();
		}
	};

	/// @brief 頂点データ
	struct SimpleVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
		XMFLOAT2 Texcoord;
	};



	/// @brief シンプルな立方体のメッシュデータ
	__declspec(align(16))
		class Mesh
	{
	protected:

		/// @brief メッシュデータ
		std::vector<MeshData> m_Mesh;
		/// @brief テクスチャデータ
		std::vector<AK_Base::PictureResource> m_Texture;

	public:
		/// @brief コンストラクタ
		Mesh();
		/// @brief デストラクタ
		virtual ~Mesh();

		/// @brief メッシュを作成
		/// @param device デバイスへのポインタ
		/// @param context デバイスコンテキストへのポインタ
		/// @param settings インポート時のパラメータ
		/// @return 正常に作成できたか
		virtual HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			std::wstring fileName = L"",
			ImportSettings* settings = nullptr) = 0;

		/// @brief メッシュの解放
		void DestroyMesh();

		/// @brief メッシュを使って描画する
		/// @param context デバイスコンテキストへのポインタ
		/// @param customFunction 描画前の任意の処理（主にシェーダー）
		/// @param textureSlot シェーダーのテクスチャスロットID
		virtual void Render(ID3D11DeviceContext* const context,
			std::function<void(int, const std::vector<MeshData>)> customFunction = nullptr,
			const UINT textureSlot = 0);

		/// @brief マテリアルを指定して描画
		/// @param context デバイスコンテキストへのポインタ
		/// @param id マテリアルのID
		/// @param textureSlot シェーダーのテクスチャスロットID
		virtual void DrawSubset(ID3D11DeviceContext* const context,
			const int id, const UINT textureSlot = 0) = 0;


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Mesh));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}
