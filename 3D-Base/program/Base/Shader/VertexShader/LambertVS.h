#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert頂点シェーダー
// 
// 製作者	: amateurK
// 作成日	: 2024/12/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "VertexShader.h"

namespace Shader {

	/// @brief コンスタントバッファ
	namespace {

		/// @brief 毎フレーム変更される数値
		struct ChangesFrame
		{
			/// @brief 3つの行列を全部掛け合わせたもの
			XMMATRIX MatrixWVP;
			/// @brief 光のベクトル（ローカル座標系）
			XMVECTOR LightDirection;
		};

		/// @brief マテリアルに関する数値
		struct Material
		{
			/// @brief 環境光の反射係数（反射率、物体の色、アルベド）
			XMFLOAT4 MaterialAmbient;
			/// @brief 拡散反射光の反射係数（反射率、物体の色、アルベド）
			XMFLOAT4 MaterialDiffuse;
		};

		/// @brief 光の強さに関する数値
		struct Light
		{
			/// @brief 環境光の強さ
			XMFLOAT4 LightAmbient;
			/// @brief 入射光の強さ
			XMFLOAT4 LightDiffuse;
		};

	}

	/// @brief Lambert頂点シェーダー
	__declspec(align(16))
		class LambertVS : public VertexShader
	{
	public:
		/// @brief コンストラクタ
		LambertVS();
		/// @brief デストラクタ
		virtual ~LambertVS();

		
		/// @brief 初期化
		/// @param params 使用するパラメータの構造体
		/// @return 成功したか
		virtual HRESULT Init(const ShaderInitParam& params) override;

		/// @brief ChageFrameコンスタントバッファを更新
		/// @param world World行列
		/// @param light 光の行列（ワールド座標系）
		/// @details 追加処理があるため、SetConstantBufferを使わないでこちらを使う
		void SetChangeFrame(const XMMATRIX& world, const XMVECTOR& light);
	};
}
