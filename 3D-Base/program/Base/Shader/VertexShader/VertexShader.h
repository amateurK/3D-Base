#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 頂点シェーダーの基底クラス
// 
// 
// 製作者	: amateurK
// 作成日	: 2024/11/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../ShaderBase.h"

namespace Shader {

	/// @brief 頂点シェーダーを初期化する際に使用するパラメーター群
	struct VertexShaderInitParam
		: public ShaderInitParam {
		/// @brief 頂点シェーダーへの入力レイアウト
		const D3D11_INPUT_ELEMENT_DESC* Layout;
		/// @brief 入力レイアウトの数
		UINT LayoutCount;
	};

	/// @brief 頂点シェーダーの基底クラス
	__declspec(align(16))
		class VertexShader : public ShaderBase
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;

	public:
		/// @brief コンストラクタ
		VertexShader();
		/// @brief デストラクタ
		virtual ~VertexShader();

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

