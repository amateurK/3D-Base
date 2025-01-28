
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// オブジェクトや生物の体力を管理するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2024/12/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Health.h"

namespace AK_Game {

	//--------------------------------------------------------------------------------------
	Health::Health(AK_Base::Actor* const parent, const int32_t& num)
		: Component(parent)
		, m_CurrentHealth(num)
		, m_MaxHealth(num)
		, m_Ratio(1.0f)
	{
	}

	//---------------------------------------------------------------------------------------------
	void Health::TakeDamage(const int32_t& num)
	{
		m_CurrentHealth -= num;

		if (m_CurrentHealth < 0) {
			m_CurrentHealth = 0;
			m_Ratio = 0.0f;
		}
		else if(m_CurrentHealth > m_MaxHealth){
			m_CurrentHealth = m_MaxHealth;
			m_Ratio = 1.0f;
		}
		else {
			m_Ratio = (float)m_CurrentHealth / (float)m_MaxHealth;
		}
	}

	//---------------------------------------------------------------------------------------------
	void Health::HealMax()
	{
		m_CurrentHealth = m_MaxHealth; 
		m_Ratio = 0;
	}

	//---------------------------------------------------------------------------------------------
	void Health::SetMaxHealthAndHeal(const int32_t& num)
	{
		SetMaxHealth(num);
		HealMax();
	}
}