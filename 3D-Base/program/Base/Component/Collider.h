#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Փ˔�����s���R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2025/01/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"
#include "Transform.h"
#include "../Collision/CollisionManager.h"

namespace AK_Base {

	class SphereCollider;

	__declspec(align(16))
		class Collider : public Component
	{
	private:
		/// @brief Transform�̍X�V��
		/// @details Transform���X�V����Ă��邩�𒲂ׂ�Ƃ��Ɏg�p
		uint32_t m_TransformChangedCount;

		/// @brief �Փˎ��̏���
		std::function<void(Collider* const)> m_OnCollision;

	public:
		/// @brief �R���X�g���N�^
		/// @param parent ���̃R���|�[�l���g�����L���Ă���Actor
		/// @param fileName �t�@�C����
		Collider(Actor* const parent)
			: Component(parent)
			, m_TransformChangedCount(0)
			, m_OnCollision(nullptr)
		{
			CollisionManager::GetInstance()->AddCollider(this);
		}
		/// @brief �f�X�g���N�^
		virtual ~Collider()
		{
			CollisionManager::GetInstance()->RemoveCollider(this);
		}

		/// @brief �R���|�[�l���g�̖��O���擾
		/// @return ���O�̕�����
		inline virtual std::string GetName() const override { return "Collider"; }


		/// @brief ����Collider�ƏՓ˂����Ƃ��̏���
		/// @param other �Փ˂���Collider
		virtual void OnCollision(Collider* const other)
		{
			if (m_OnCollision != nullptr)
			{
				m_OnCollision(other);
			}
		};

		/// @brief �Փˎ��̏�����ݒ�
		/// @param func �Փˎ��Ɏ��s����֐�
		void SetOnCollision(const std::function<void(Collider* const)>& func)
		{
			m_OnCollision = func;
		}

		/// @brief �Փ˂��Ă��邩�𒲂ׂ�
		/// @param other ������s��Collider
		/// @return �Փ˂��Ă���Ȃ�true
		virtual bool CheckCollision(Collider* const other) = 0;

		/// @brief ���̂ƏՓ˂��Ă��邩�𒲂ׂ�
		/// @param other ������s������
		/// @return �Փ˂��Ă���Ȃ�true
		virtual bool CheckCollisionWithSphere(SphereCollider* const other) = 0;

		/// @brief ��΍��W���X�V����K�v������΍X�V
		inline void CheckAbsolutePosUpdate() {
			if (CheckTransformUpdate()) {
				UpdateAbsolutePos();
			}
		}

	private:

		/// @brief ���΍��W�Ɋ�Â��Đ�΍��W���X�V
		virtual void UpdateAbsolutePos() = 0;

		/// @brief Transform���X�V���ꂽ�����`�F�b�N
		/// @return �X�V����Ă����ꍇtrue
		inline bool CheckTransformUpdate() {
			auto cnt = m_ParentActor->GetTransform()->GetChengedCount();
			// Transform���ύX����Ă���ꍇ
			if (m_TransformChangedCount != cnt)
			{
				m_TransformChangedCount = cnt;
				return true;
			}
			return false;
		}
	};
}