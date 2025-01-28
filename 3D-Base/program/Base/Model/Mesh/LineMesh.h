#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 直線のメッシュデータ
// 
// 製作者	: amateurK
// 作成日	: 2025/01/27
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h"

namespace Mesh {

	/// @brief VRMファイルから読み込んだメッシュを管理するクラス
	__declspec(align(16))
		class LineMesh : public Mesh
	{
	private:



	public:
		/// @brief コンストラクタ
		LineMesh();
		/// @brief デストラクタ
		virtual ~LineMesh();

		/// @brief メッシュを作成
		/// @param device デバイスへのポインタ
		/// @param context デバイスコンテキストへのポインタ
		/// @param fileName 不要
		/// @param settings インポート時のパラメータ
		/// @return 正常に作成できたか
		virtual HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			const std::wstring fileName = L"",
			ImportSettings* settings = nullptr
		) override;

		/// @brief マテリアルを指定して描画
		/// @param context デバイスコンテキストへのポインタ
		/// @param id マテリアルのID
		/// @param testureSlot シェーダーのテクスチャスロットID
		virtual void DrawSubset(ID3D11DeviceContext* const context, const int id, const UINT testureSlot = 0);


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(LineMesh));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}
