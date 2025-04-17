#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �I�u�W�F�N�g�␶���̗̑͂��Ǘ�����R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2024/12/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Base/Component.h"

namespace AK_Game {

	class Health : public AK_Base::Component
	{
	private:
		/// @brief ���݂�Health
		int32_t m_CurrentHealth;
		/// @brief �ő�Health
		int32_t m_MaxHealth;

		/// @brief �̗͂̊����iCurrent / Max�j
		float m_Ratio;

	public:
		/// @brief �R���X�g���N�^
		/// @param parent ���̃R���|�[�l���g�����L���Ă���Actor
		/// @param num �ő�̗�
		Health(AK_Base::Actor* const parent, const int32_t& num = -1);
		/// @brief �f�X�g���N�^
		virtual ~Health() = default;

		/// @brief �R���|�[�l���g�̖��O���擾
		/// @return ���O�̕�����
		inline virtual std::string GetName() const override { return "Health"; }

		/// @brief �_���[�W���󂯂�
		/// @param num ��_���[�W�̐��l
		void TakeDamage(const int32_t& num);

		/// @brief Health���c���Ă��邩
		/// @return �c���Ă�����true
		inline bool IsAlive() { return m_CurrentHealth ? true : false; }

		/// @brief Health��S������
		void HealMax();

		/// @brief �ő�̗͂��Z�b�g���ĉ񕜂�����
		/// @param num �ő�̗�
		void SetMaxHealthAndHeal(const int32_t& num);

		// �Q�b�^�[�E�Z�b�^�[

		inline int32_t GetCurrentHealth() const { return m_CurrentHealth; }
		inline int32_t GetMaxHealth() const { return m_MaxHealth; }
		inline float GetRatio() const { return m_Ratio; }
		inline void SetCurrentHealth(const int32_t& num) { m_CurrentHealth = num; }
		inline void SetMaxHealth(const int32_t& num) { m_MaxHealth = num; }

	};
}
