#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// FBXファイルから読み込むメッシュデータ
// 
// Assimp_native_4.1_v142を使用
// ツール -> NuGetパッケージマネージャ -> ソリューションのNuGetパッケージの管理
//   からパッケージソースがnuget.orgの状態で検索をかけると出てくる
// Assimpにも種類がいろいろある？どれがいいのかは不明
// 追加のインクルードディレクトリに以下を追加すると便利
// 　$(SolutionDir)packages\Assimp_native_4.1_v142.4.1.0\build\native\include
// プロパティ -> ビルドイベント -> ビルド後のイベントにこれを入力するとdllを自動でexeの横に置いてくれる
//   xcopy /Y "$(SolutionDir)packages\Assimp_native_4.1_v142.4.1.0\build\native\lib\x64-Debug\*.dll" "$(OutDir)"
// 
// 
// 製作者	: amateurK
// 作成日	: 2024/08/05
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h"


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

	/// @brief シンプルな立方体のメッシュデータ
	__declspec(align(16))
		class FbxMesh : public Mesh
	{
	private:



	public:
		/// @brief コンストラクタ
		FbxMesh();
		/// @brief デストラクタ
		virtual ~FbxMesh();

		/// @brief メッシュの解放
		void DestroyMesh();

		/// @brief メッシュを作成
		/// @param device デバイスへのポインタ
		/// @param context デバイスコンテキストへのポインタ
		/// @param fileName FBXファイル名
		/// @return 正常に作成できたか
		virtual HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			const std::wstring fileName = L"") override;
		/// @brief メッシュを作成
		/// @param device デバイスへのポインタ
		/// @param context デバイスコンテキストへのポインタ
		/// @param fileName FBXファイル名
		/// @param settings インポート時のパラメータ
		/// @return 正常に作成できたか
		HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			const std::wstring fileName = L"",
			ImportSettings* settings = nullptr
			);

		/// @brief マテリアルを指定して描画
		/// @param context デバイスコンテキストへのポインタ
		/// @param id マテリアルのID
		/// @param testureSlot シェーダーのテクスチャスロットID
		virtual void DrawSubset(ID3D11DeviceContext* const context, const int id, const UINT testureSlot = 0);


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(FbxMesh));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}
