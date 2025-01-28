#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// オブジェクトや生物の体力を管理するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2024/12/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Base/Component.h"

namespace AK_Game {

	class Health : public AK_Base::Component
	{
	private:
		/// @brief 現在のHealth
		int32_t m_CurrentHealth;
		/// @brief 最大Health
		int32_t m_MaxHealth;

		/// @brief 体力の割合（Current / Max）
		float m_Ratio;

	public:
		/// @brief コンストラクタ
		/// @param parent このコンポーネントを所有しているActor
		/// @param num 最大体力
		Health(AK_Base::Actor* const parent, const int32_t& num = -1);
		/// @brief デストラクタ
		virtual ~Health() = default;

		/// @brief コンポーネントの名前を取得
		/// @return 名前の文字列
		inline virtual std::string GetName() const override { return "Health"; }

		/// @brief ダメージを受ける
		/// @param num 被ダメージの数値
		void TakeDamage(const int32_t& num);

		/// @brief Healthが残っているか
		/// @return 残っていたらtrue
		inline bool IsAlive() { return m_CurrentHealth ? true : false; }

		/// @brief Healthを全快する
		void HealMax();

		/// @brief 最大体力をセットして回復させる
		/// @param num 最大体力
		void SetMaxHealthAndHeal(const int32_t& num);

		// ゲッター・セッター

		inline int32_t GetCurrentHealth() const { return m_CurrentHealth; }
		inline int32_t GetMaxHealth() const { return m_MaxHealth; }
		inline float GetRatio() const { return m_Ratio; }
		inline void SetCurrentHealth(const int32_t& num) { m_CurrentHealth = num; }
		inline void SetMaxHealth(const int32_t& num) { m_MaxHealth = num; }

	};
}
