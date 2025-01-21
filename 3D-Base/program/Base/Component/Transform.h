#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���S���W�A��]�A�X�P�[����ێ�����R���|�[�l���g
// ���ʂ�+Z���A���+Y���A�E��+X���Ƃ��Ă���B
// 
// �����	: amateurK
// �쐬��	: 2024/11/18
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"

namespace AK_Base {

	/// @brief ���S���W�A��]�A�X�P�[����ێ�����R���|�[�l���g
	__declspec(align(16))
	class Transform : public Component
	{
	private:
		/// @brief ���ݍ��W
		DirectX::XMVECTOR m_Position;
		/// @brief ��]�p�x�i�N�H�[�^�j�I���j
		DirectX::XMVECTOR m_Rotation;
		/// @brief �X�P�[��
		DirectX::XMVECTOR m_Scale;

		/// @brief ���[���h�s��
		DirectX::XMMATRIX m_World;
		/// @brief �X�V�����������ifalse�Ȃ�World�s����g���܂킷�j
		bool m_IsChanged;

		/// @brief �X�V�����ꂽ��
		uint32_t m_ChangedCount;

		Transform* m_Parent;
		std::vector<Transform*> m_Children;

	public:
		/// @brief �R���X�g���N�^
		/// @param parent ���̃R���|�[�l���g�����L���Ă���Actor
		/// @param addChild �eActor��Transform�������Ă���Ƃ��ɐe�q�֌W�ɂ��邩
		Transform(Actor* const parent, bool addChild = true);
		/// @brief �f�X�g���N�^
		virtual ~Transform() = default;

		/// @brief �R���|�[�l���g�̖��O���擾
		/// @return ���O�̕�����
		inline virtual std::string GetName() const override{ return "Transform"; }


		/// @brief ���ݒn����w�肵�������ړ�
		/// @param offset �ړ���
		void Translate(const DirectX::XMVECTOR& offset);
		/// @brief ���ݒn����w�肵�������ړ�
		/// @param x x�������̈ړ���
		/// @param y y�������̈ړ���
		/// @param z z�������̈ړ���
		void Translate(float x, float y, float z);

		/// @brief ���ʕ�������Ɉړ�����
		/// @param offset �ړ���(right, up, forword, 0.0f)
		void Move(const DirectX::XMVECTOR& offset);
		/// @brief ���ʕ�������Ɉړ�����
		/// @param forward ���ʕ����̈ړ���
		/// @param right �E�����̈ړ���
		/// @param up ������̈ړ���
		void Move(float forward, float right, float up);


		/// @brief ���݂̊p�x�����]
		/// @param axis ��]���鎲
		/// @param angle �p�x
		void Rotate(const DirectX::XMVECTOR& axis, float angle);
		/// @brief ���݂̊p�x�����]
		/// @param axis ���K���ς݂̉�]���鎲�i���K�����Ă��Ȃ��Ȃ�Rotate()���g���j
		/// @param angle �p�x
		void RotateNorm(const DirectX::XMVECTOR& axis, float angle);

		/// @brief ���݂̊p�x���烍�[�J�������W�n�ŉ�]
		/// @param axis ��]���鎲
		/// @param angle �p�x
		void RotateLocal(const DirectX::XMVECTOR& axis, float angle);

		/// @brief X���𒆐S�ɉ�]
		/// @param angle �p�x
		void RotateX(float angle);
		/// @brief Y���𒆐S�ɉ�]
		/// @param angle �p�x
		void RotateY(float angle);
		/// @brief Z���𒆐S�ɉ�]
		/// @param angle �p�x
		void RotateZ(float angle);

		/// @brief X���𒆐S�ɉ�]
		/// @param angle �p�x
		void RotateLocalX(float angle);
		/// @brief Y���𒆐S�ɉ�]
		/// @param angle �p�x
		void RotateLocalY(float angle);
		/// @brief Z���𒆐S�ɉ�]
		/// @param angle �p�x
		void RotateLocalZ(float angle);

		/// @brief �w�肵�����W�Ɍ��������킹��
		/// @param position ���W
		void LookAtPosition(const DirectX::XMVECTOR& position);


		/// @brief �g��k��
		/// @param mul �{��
		void Scale(float mul);
		/// @brief �g��k��
		/// @param mul �{��
		void Scale(const DirectX::XMVECTOR& mul);


		/// @brief IsChanged��true�ɂ���
		void MarkChanged();




		// �Q�b�^�[�Z�b�^�[

		inline const DirectX::XMVECTOR& GetPosition() const { return m_Position; }
		void SetPosition(const DirectX::XMVECTOR& position);
		void SetPosition(float x, float y, float z);

		inline const DirectX::XMVECTOR& GetRotation() const { return m_Rotation; }
		void SetRotation(const DirectX::XMVECTOR& rotation);
		void SetRotation(float x, float y, float z, float w);

		inline const DirectX::XMVECTOR& GetScele() const { return m_Scale; }
		void SetScele(const DirectX::XMVECTOR& scale);
		void SetScele(float x, float y, float z);

		const DirectX::XMMATRIX* GetWorldMatrix();

		inline const uint32_t GetChengedCount() const { return m_ChangedCount; }

		inline Transform* GetParent() const { return m_Parent; }
		void SetParent(Transform* parent);

		void AddChild(Transform* child);


	};

}