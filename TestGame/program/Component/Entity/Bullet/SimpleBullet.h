#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 直進する弾コンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2025/04/14
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Base/Component.h"

namespace AK_Game {

	class SimpleBullet : public AK_Base::Component
	{
	private:
		/// @brief 現在の速度(m/s)
		DirectX::XMVECTOR m_Speed;

		/// @brief 弾のライフタイム
		float m_LifeTime;

	public:
		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor
		SimpleBullet(AK_Base::Actor* const parent);
		/// @brief デストラクタ
		virtual ~SimpleBullet() = default;

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override { return "SimpleBullet"; }

		/// @brief 更新
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のUpdate()からの経過時間（秒）
		virtual void Update(const double& totalTime, const float& elapsedTime) override;

		/// @brief 通常移動時の速度(m/s)
		/// @param vec XMVectorSet(right, up, forword, 0.0f)
		inline void SetSpeed(const DirectX::XMVECTOR& vec) { m_Speed = vec; }
		/// @brief 通常移動時の速度(m/s)
		inline void SetSpeed(float forword, float right, float up) { m_Speed = DirectX::XMVectorSet(right, up, forword, 0.0f); }
		/// @brief 弾のライフタイム
		inline void SetLifeTime(float sec) { m_LifeTime = sec; }
	};
}
