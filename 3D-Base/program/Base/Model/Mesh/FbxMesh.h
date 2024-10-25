#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// FBXファイルから読み込むメッシュデータ
// 
// 製作者	: amateurK
// 作成日	: 2024/08/05
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h"

namespace Mesh {

	/// @brief シンプルな立方体のメッシュデータ
	__declspec(align(16))
		class FbxMesh
		: public Mesh
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
