#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// プレイヤーの移動を制御するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2025/01/07
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Base/Component.h"

namespace AK_Game {

	class PlayerMovement : public AK_Base::Component
	{
	private:
		/// @brief 現在の速度(m/s)
		DirectX::XMVECTOR m_Speed;

		/// @brief 通常移動時の加速度(m/s^2)
		DirectX::XMVECTOR m_NormalAccel;

		/// @brief 空気抵抗(m/s^2)
		/// @details 乗算するので、1から抵抗を引いた値を入れる
		float m_AirResistance;

	public:
		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor
		PlayerMovement(AK_Base::Actor* const parent);
		/// @brief デストラクタ
		virtual ~PlayerMovement() = default;

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override { return "PlayerMovement"; }

		/// @brief 更新
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のUpdate()からの経過時間（秒）
		virtual void Update(const double& totalTime, const float& elapsedTime) override;


		/// @brief 通常移動時の加速度(m/s^2)
		/// @param vec XMVectorSet(right, up, forword, 0.0f)
		inline void SetNormalAccel(const DirectX::XMVECTOR& vec) { m_NormalAccel = vec; }
		/// @brief 通常移動時の加速度(m/s^2)
		inline void SetNormalAccel(float right, float up, float forword) { m_NormalAccel = DirectX::XMVectorSet(right, up, forword, 0.0f); }
		/// @brief 空気抵抗(m/s^2)
		inline void SetAirResistance(float r) { m_AirResistance = r; }
	};
}
