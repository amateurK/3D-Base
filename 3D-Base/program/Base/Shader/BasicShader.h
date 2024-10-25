#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 陰などがない基本的なシェーダー
// 
// 製作者	: amateurK
// 作成日	: 2024/04/20
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Shader.h"

namespace Shader {

	struct ChangesFrame
	{
		/// @brief 3つの行列を全部掛け合わせたもの
		XMMATRIX matrixWVP;
	};

	/// @brief 陰などがない基本的なシェーダー
	__declspec(align(16))
	class BasicShader
		: public Shader
	{
	private:

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_ChangesFrame;

	public:
		/// @brief コンストラクタ
		BasicShader();
		/// @brief デストラクタ
		virtual ~BasicShader();


		/// @brief レンダリングの準備
		virtual void SetRendering() override;


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(BasicShader));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}

	private:
		/// @brief シェーダーを作成
		/// @return 成功したか
		/// @details シェーダーのコンパイルや設定などを行う。長すぎるのでわけただけ
		virtual HRESULT Create() override;

	};
}