#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// シンプルな立方体のメッシュデータ
// 
// 製作者	: amateurK
// 作成日	: 2024/07/26
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h"

namespace Mesh {

	/// @brief シンプルな立方体のメッシュデータ
	__declspec(align(16))
		class BasicMesh
		: public Mesh
	{
	private:


	public:
		/// @brief コンストラクタ
		BasicMesh();
		/// @brief デストラクタ
		virtual ~BasicMesh() = default;

		/// @brief メッシュを作成
		/// @param device デバイスへのポインタ
		/// @param context デバイスコンテキストへのポインタ
		/// @return 正常に作成できたか
		/// @details ファイルから読み込む場合はオーバーロードして作る
		virtual HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			std::wstring fileName = L"") override;

		/// @brief マテリアルを指定して描画
		/// @param context デバイスコンテキストへのポインタ
		/// @param id マテリアルのID
		/// @param testureSlot シェーダーのテクスチャスロットID
		virtual void DrawSubset(ID3D11DeviceContext* const context, const int id, const UINT testureSlot = 0);


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(BasicMesh));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}