#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �v���C���[�̈ړ��𐧌䂷��R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2025/01/07
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Base/Component.h"

namespace AK_Game {

	class PlayerMovement : public AK_Base::Component
	{
	private:
		/// @brief ���݂̑��x(m/s)
		DirectX::XMVECTOR m_Speed;

		/// @brief �ʏ�ړ����̉����x(m/s^2)
		DirectX::XMVECTOR m_NormalAccel;

		/// @brief ��C��R(m/s^2)
		/// @details ��Z����̂ŁA1�����R���������l������
		float m_AirResistance;

	public:
		/// @brief �R���X�g���N�^
		/// @param parent ���̃R���|�[�l���g�����L���Ă���Actor
		PlayerMovement(AK_Base::Actor* const parent);
		/// @brief �f�X�g���N�^
		virtual ~PlayerMovement() = default;

		/// @brief �R���|�[�l���g�̖��O���擾
		/// @return ���O�̕�����
		inline virtual std::string GetName() const override { return "PlayerMovement"; }

		/// @brief �X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Update()����̌o�ߎ��ԁi�b�j
		virtual void Update(const double& totalTime, const float& elapsedTime) override;


		/// @brief �ʏ�ړ����̉����x(m/s^2)
		/// @param vec XMVectorSet(right, up, forword, 0.0f)
		inline void SetNormalAccel(const DirectX::XMVECTOR& vec) { m_NormalAccel = vec; }
		/// @brief �ʏ�ړ����̉����x(m/s^2)
		inline void SetNormalAccel(float right, float up, float forword) { m_NormalAccel = DirectX::XMVectorSet(right, up, forword, 0.0f); }
		/// @brief ��C��R(m/s^2)
		inline void SetAirResistance(float r) { m_AirResistance = r; }
	};
}
