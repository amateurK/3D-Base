#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ピクセルシェーダーの基底クラス
// 
// 
// 製作者	: amateurK
// 作成日	: 2024/12/04
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../ShaderBase.h"

namespace Shader {

	/// @brief ピクセルシェーダーの基底クラス
	__declspec(align(16))
		class PixelShader : public ShaderBase
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

	public:
		/// @brief コンストラクタ
		PixelShader();
		/// @brief デストラクタ
		virtual ~PixelShader();

		/// @brief 初期化
		/// @param params 使用するパラメータの構造体
		/// @return 成功したか
		virtual HRESULT Init(const ShaderInitParam& params) override;

		/// @brief シェーダーをGPUにセットする
		/// @param set ShaderSetのポインタ
		virtual void SetShader(const ShaderSet* set) override;

		/// @brief コンスタントバッファをバインド
		/// @param index バインドするコンスタントバッファのインデックス
		virtual void UpdateGPUConstantBuffer(size_t index) override;

	};
}
