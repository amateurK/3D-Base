#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert頂点シェーダー
// スキニングアニメーションも行う
// 
// 製作者	: amateurK
// 作成日	: 2025/02/14
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "LambertVS.h"

namespace Shader {

	/// @brief Lambert頂点シェーダー
	__declspec(align(16))
		class LambertSkinningVS : public LambertVS
	{
	public:

		/// @brief ボーンの行列
		struct Bones
		{
			DirectX::XMMATRIX BoneMatrix[100];
		};

	public:
		/// @brief コンストラクタ
		LambertSkinningVS();
		/// @brief デストラクタ
		virtual ~LambertSkinningVS();


		/// @brief 初期化
		/// @param params 使用するパラメータの構造体
		/// @return 成功したか
		virtual HRESULT Init(const ShaderInitParam& params) override;

		/// @brief シェーダーをGPUにセットする
		/// @param set ShaderSetのポインタ
		virtual void SetShader(const ShaderSet* set) override;

		/// @brief オブジェクトごとに変更される値をGPUにセットする
		/// @param set ShaderSetのポインタ
		virtual void SetPerObject(const ShaderSet* set) override;

		/// @brief シェーダーで使用される値をShaderSetに追加
		/// @param set ShaderSetのポインタ
		virtual void AddDataForShaderSet(ShaderSet* set) const override;
	};
}
