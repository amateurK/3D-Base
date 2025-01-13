#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���̂�Collider�����R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2025/01/11
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Collider.h"
#include "../../Math/primitive.h"
#include "../../Math/AK_Math.h"

namespace AK_Base {

	__declspec(align(16))
		class SphereCollider : public Collider
	{
	private:

		/// @brief ���΍��W
		/// @details �eActor�̃��[�J�����W�n
		AK_Math::Sphere3 m_Relative;
		/// @brief ��΍��W
		/// @details ���[���h���W�n
		AK_Math::Sphere3 m_Absolute;

	public:
		/// @brief �R���X�g���N�^
		/// @param parent ���̃R���|�[�l���g�����L���Ă���Actor
		/// @param fileName �t�@�C����
		SphereCollider(Actor* const parent, AK_Math::Sphere3 sphere = {})
			: Collider(parent)
			, m_Relative(sphere)
			, m_Absolute(sphere)
		{
			UpdateAbsolutePos();
		}
		/// @brief �f�X�g���N�^
		virtual ~SphereCollider() = default;

		/// @brief �R���|�[�l���g�̖��O���擾
		/// @return ���O�̕�����
		inline virtual std::string GetName() const override { return "SphereCollider"; }

		/// @brief �Փ˂��Ă��邩�𒲂ׂ�
		/// @param other ������s��Collider
		/// @return �Փ˂��Ă���Ȃ�true
		inline virtual bool CheckCollision(Collider* const other) override
		{
			return other->CheckCollisionWithSphere(this);
		}
		inline virtual bool CheckCollisionWithSphere(SphereCollider* const other) override
		{
			// Sphere x Sphere
			return AK_Math::IsCollide(m_Absolute, other->m_Absolute);
		}

		// �Z�b�^�[

		void SetCollider(const AK_Math::Sphere3& sphere)
		{
			m_Relative = sphere;
			UpdateAbsolutePos();
		}

	private:
		/// @brief ���΍��W�Ɋ�Â��Đ�΍��W���X�V
		virtual void UpdateAbsolutePos() override
		{
			// ���[�J�����W�n�����[���h���W�n�ɕϊ�
			m_Absolute.point = XMVector3Transform(m_Relative.point, *m_ParentActor->GetTransform()->GetWorldMatrix());

			// �T�C�Y�ɂ���Ĕ��a���ς�邪�A�ȉ~�͕ʂ̏����ɂȂ�̂�x���W�Ŕ��f
			m_Absolute.radius = m_Relative.radius * m_ParentActor->GetTransform()->GetScele().m128_f32[0];
		}
	};
}