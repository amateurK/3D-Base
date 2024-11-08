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

	/// @brief メッシュデータ
	struct MeshData
	{
		/// @brief 頂点の数
		uint32_t NumVertex;
		/// @brief 面の数
		uint32_t NumFace;

		/// @brief マテリアルの数
		uint32_t NumMaterial;

		//Mesh() {
		//	//ZeroMemory(this, sizeof(Mesh));
		//	// memo IndexBufferをゼロクリアしているので、vectorを初期化しないとだめかも
		//	// vectorをZeroMemory()するとメモリリークが発生する
		//	// おそらく、vector内部の変数（ポインタ？）が壊れて、そのポインタの先のものが削除されていないから？
		//}
		
		/// @brief デストラクタ
		~MeshData() = default;
	};

	/// @brief マテリアルデータ
	struct MaterialData
	{
		/// @brief このマテリアルを使用しているポリゴンの頂点バッファ
		Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
		/// @brief このマテリアルを使用しているポリゴンのインデックスバッファ
		Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer;
		/// @brief このマテリアルを使用している頂点の数
		uint32_t NumVertex;
		/// @brief このマテリアルを使用しているポリゴン数
		uint32_t NumFace;
		/// @brief 使用されているテクスチャ
		AK_Base::PictureResource Texture;

		/// @brief デストラクタ
		~MaterialData() 
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
		std::unique_ptr<MeshData> m_Mesh;
		/// @brief マテリアル
		std::vector<MaterialData> m_Material;

		///// @brief インデックスバッファ（元データ）
		//int* m_IndexBuffer;
		///// @brief 頂点バッファ（元データ）
		//SimpleVertex* m_VertexBuffer;

	public:
		/// @brief コンストラクタ
		Mesh();
		/// @brief デストラクタ
		virtual ~Mesh();

		/// @brief メッシュを作成
		/// @param device デバイスへのポインタ
		/// @param context デバイスコンテキストへのポインタ
		/// @return 正常に作成できたか
		virtual HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			std::wstring fileName = L"") = 0;

		/// @brief メッシュの解放
		void DestroyMesh();

		/// @brief メッシュを使って描画する
		/// @param context デバイスコンテキストへのポインタ
		/// @param customFunction 描画前の任意の処理（主にシェーダー）
		/// @param textureSlot シェーダーのテクスチャスロットID
		virtual void Render(ID3D11DeviceContext* const context,
			std::function<void(int, const std::vector<MaterialData>)> customFunction = nullptr,
			const UINT textureSlot = 0);

		/// @brief マテリアルを指定して描画
		/// @param context デバイスコンテキストへのポインタ
		/// @param id マテリアルのID
		/// @param testureSlot シェーダーのテクスチャスロットID
		virtual void DrawSubset(ID3D11DeviceContext* const context, const int id, const UINT testureSlot = 0) = 0;


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Mesh));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}
