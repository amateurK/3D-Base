#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���i����e�R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2025/04/14
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Base/Component.h"

namespace AK_Game {

	class SimpleBullet : public AK_Base::Component
	{
	private:
		/// @brief ���݂̑��x(m/s)
		DirectX::XMVECTOR m_Speed;

		/// @brief �e�̃��C�t�^�C��
		float m_LifeTime;

	public:
		/// @brief �R���X�g���N�^
		/// @param parent ���̃R���|�[�l���g�����L���Ă���Actor
		SimpleBullet(AK_Base::Actor* const parent);
		/// @brief �f�X�g���N�^
		virtual ~SimpleBullet() = default;

		/// @brief �R���|�[�l���g�̖��O���擾
		/// @return ���O�̕�����
		inline virtual std::string GetName() const override { return "SimpleBullet"; }

		/// @brief �X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Update()����̌o�ߎ��ԁi�b�j
		virtual void Update(const double& totalTime, const float& elapsedTime) override;

		/// @brief �ʏ�ړ����̑��x(m/s)
		/// @param vec XMVectorSet(right, up, forword, 0.0f)
		inline void SetSpeed(const DirectX::XMVECTOR& vec) { m_Speed = vec; }
		/// @brief �ʏ�ړ����̑��x(m/s)
		inline void SetSpeed(float forword, float right, float up) { m_Speed = DirectX::XMVectorSet(right, up, forword, 0.0f); }
		/// @brief �e�̃��C�t�^�C��
		inline void SetLifeTime(float sec) { m_LifeTime = sec; }
	};
}
