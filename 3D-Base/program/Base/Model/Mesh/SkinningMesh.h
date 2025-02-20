#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// スキニングアニメーションを行うメッシュデータクラス
// 抽象クラス
// 
// 製作者	: amateurK
// 作成日	: 2025/02/08
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h" 

namespace Mesh {

	/// @brief スキニングアニメーションに使用するデータ
	struct SkinningData
	{
		/// @brief 各頂点が影響を受けるボーン
		std::vector<std::array<uint8_t, 4>> BoneIndices;
		/// @brief 影響を受けるボーンの重み
		std::vector<std::array<float, 4>> BoneWeights;
	};

	/// @brief ボーンデータ
	struct BoneData
	{
		/// @brief ボーンid
		int ID;
		/// @brief ボーン名
		std::string Name;
		/// @brief 初期状態での逆バインド行列
		DirectX::XMMATRIX InverseBindMatrix;
		/// @brief ローカル変換行列
		DirectX::XMMATRIX LocalMatrix;
		/// @brief 1番目の子ボーン
		BoneData* FirstChild;
		/// @brief 次の兄弟ボーン
		BoneData* NextSibling;
	};

	/// @brief 頂点データ
	struct SkinningVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 Texcoord;
		uint8_t BoneIndices[4];
		DirectX::XMFLOAT4 BoneWeight;
	};

	/// @brief スキニングアニメーションを行うメッシュデータ
	__declspec(align(16))
	class SkinningMesh : public Mesh
	{
	protected:
		/// @brief スキニングアニメーションに使用するデータ
		/// @details Meshクラスのm_Meshに対応
		std::vector<SkinningData> m_SkinningData;

		/// @brief ボーンデータ
		/// @details indexがBoneのidと対応している
		std::vector<BoneData> m_BoneData;

		/// @brief ボーンデータを文字列で検索するためのハッシュマップ
		/// @details キー : ボーン名
		/// @details 値　 : SkinningDataのインデックス
		std::unordered_map<std::string, BoneData*> m_BoneDataHashmap;

	public:
		/// @brief コンストラクタ
		SkinningMesh();
		/// @brief デストラクタ
		virtual ~SkinningMesh() = default;

		/// @brief メッシュを作成
		/// @param device デバイスへのポインタ
		/// @param context デバイスコンテキストへのポインタ
		/// @param settings インポート時のパラメータ
		/// @return 正常に作成できたか
		virtual HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			std::wstring fileName = L"",
			ImportSettings* settings = nullptr) override = 0;

		/// @brief マテリアルを指定して描画
		/// @param context デバイスコンテキストへのポインタ
		/// @param id マテリアルのID
		/// @param textureSlot シェーダーのテクスチャスロットID
		virtual void DrawSubset(ID3D11DeviceContext* const context,
			const int id, const UINT textureSlot = 0) override = 0;



		/// @brief ボーンの配列を渡す
		inline const std::vector<BoneData>& GetBoneData() const { return m_BoneData; }

		/// @brief ボーンの数を返す
		inline size_t GetBoneDataSize() const { return m_BoneData.size(); }
	};
}