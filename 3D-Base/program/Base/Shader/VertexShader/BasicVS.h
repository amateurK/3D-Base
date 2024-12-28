#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 普通の頂点シェーダー
// 
// 製作者	: amateurK
// 作成日	: 2024/12/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "VertexShader.h"

namespace Shader {

	/// @brief 普通の頂点シェーダー
	__declspec(align(16))
		class BasicVS : public VertexShader
	{
	public:
		/// @brief 毎フレーム変更される数値
		struct ChangesFrame
		{
			/// @brief 3つの行列を全部掛け合わせたもの
			XMMATRIX MatrixWVP;
		};

		/// @brief マテリアルに関する数値
		struct Material
		{
			/// @brief 乗算する色
			XMFLOAT4 Color;
		};

	public:
		/// @brief コンストラクタ
		BasicVS();
		/// @brief デストラクタ
		virtual ~BasicVS();


		/// @brief 初期化
		/// @param params 使用するパラメータの構造体
		/// @return 成功したか
		virtual HRESULT Init(const ShaderInitParam& params) override;

		/// @brief オブジェクトごとに変更される値をGPUにセットする
		/// @param set ShaderSetのポインタ
		virtual void SetPerObject(const ShaderSet* set) override;

		/// @brief シェーダーで使用される値をShaderSetに追加
		/// @param set ShaderSetのポインタ
		virtual void AddDataForShaderSet(ShaderSet* set) const override;

		/// @brief ChageFrameコンスタントバッファを更新
		/// @param world World行列
		/// @details 追加処理があるため、SetConstantBufferを使わないでこちらを使う
		void SetChangeFrame(const XMMATRIX& world);
	};
}
