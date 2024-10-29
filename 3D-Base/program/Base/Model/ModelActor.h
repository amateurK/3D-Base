#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 3Dモデルを持ったオブジェクトが継承するクラス
// 
// 製作者	: amateurK
// 作成日	: 2024/04/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Actor.h"
#include "ModelRender.h"

namespace AK_Base {

	/// @brief 3Dモデルを持つアクター
	__declspec(align(16))
		class ModelActor : public Actor
	{
	protected:
		/// @brief 3Dモデルの描画管理クラス
		std::unique_ptr<ModelRender> m_ModelRender;

		/// @brief ワールド行列
		DirectX::XMMATRIX m_WorldMatrix;
		/// @brief 現在座標
		DirectX::XMFLOAT3A m_Position;
		/// @brief 回転角度
		float m_Rotation;
		/// @brief スケール
		DirectX::XMFLOAT3A m_Scale;

		/// @brief 表示するか
		/// @details true = 表示
		bool m_IsVisible;

	public:
		/// @brief コンストラクタ
		/// @param shader 使用するシェーダーへのポインタ
		/// @param name 識別名
		/// @param fileName 使用するメッシュのファイル名
		ModelActor(
			Shader::Shader* const shader
			, std::wstring name = L"unnamed"
			, std::wstring fileName = L""
		);

		/// @brief デストラクタ
		virtual ~ModelActor();

		
		/// @brief 更新
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のMove()からの経過時間（秒）
		virtual void Move(const double& totalTime, const float& elapsedTime) override;
		/// @brief 描画
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のRender()からの経過時間（秒）
		virtual void Render(const double& totalTime, const float& elapsedTime) override;

		/// @brief ワールド行列を更新する
		/// @details オーバーライドされる想定
		virtual void CalcWorldMatrix();
		

		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(ModelActor));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}