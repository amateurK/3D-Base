#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambertシェーダークラス
// 
// 製作者	: amateurK
// 作成日	: 2024/08/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Shader.h"

namespace Shader {

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


	/// @brief 陰などがない基本的なシェーダー
	__declspec(align(16))
		class LambertShader
		: public Shader
	{
	private:

		/// @brief 毎フレーム変更される数値が格納されているコンスタントバッファ
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_ChangesFrame;
		/// @brief マテリアルに関する数値が格納されているコンスタントバッファ
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Material;
		/// @brief 光の強さに関する数値が格納されているコンスタントバッファ
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Light;

	public:
		/// @brief コンストラクタ
		LambertShader();
		/// @brief デストラクタ
		virtual ~LambertShader();


		/// @brief レンダリングの準備
		virtual void SetRendering() override;

		/// @brief ChangeFrameコンスタントバッファを更新
		/// @param lightDirection 光の位置（ワールド座標）
		void SetChangesFrame(const XMVECTOR& lightDirection);

		/// @brief Materialコンスタントバッファを更新
		/// @param materialAmbient 環境光の反射係数
		/// @param materialDiffuse 拡散反射光の反射係数
		void SetMaterial(const XMFLOAT4& materialAmbient, const XMFLOAT4& materialDiffuse);
		
		/// @brief Lightコンスタントバッファを更新
		/// @param lightAmbient 環境光の強さ
		/// @param lightDiffuse 入射光の強さ
		void SetLight(const XMFLOAT4& lightAmbient, const XMFLOAT4& lightDiffuse);


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(LambertShader));
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