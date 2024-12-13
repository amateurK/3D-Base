
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���S���W�A��]�A�X�P�[����ێ�����R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2024/11/18
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Transform.h"
#include "../Tools/Alignment.h"

namespace AK_Base {

	//--------------------------------------------------------------------------------------
	Transform::Transform(Actor* const parent, bool addChild)
		: Component(parent)
		, m_Position{ 0.0f, 0.0f, 0.0f }
		, m_Rotation{ 0.0f, 0.0f, 0.0f, 1.0f }
		, m_Scale{ 1.0f, 1.0f, 1.0f }
		, m_World(XMMatrixIdentity())
		, m_IsChanged(true)
		, m_Parent(nullptr)
	{
		Tools::CheckAlignment(this);

		m_Children.clear();
		if (addChild) {
			auto parent = GetActor()->GetParent();
			if (parent != nullptr) {
				auto comp = parent->GetComponent<Transform>();
				if (comp != nullptr) {
					SetParent(comp);
				}
			}
		}

		GetActor()->SetTransform(this);
	}

	//--------------------------------------------------------------------------------------
	void Transform::Translate(const DirectX::XMVECTOR& offset)
	{
		m_Position += offset;
		MarkChanged();
	}
	//--------------------------------------------------------------------------------------
	void Transform::Translate(float x, float y, float z)
	{
		Translate(XMVectorSet(x, y, z, 1.0f));
	}

	//--------------------------------------------------------------------------------------
	void Transform::Rotate(const DirectX::XMVECTOR& axis, float angle)
	{
		RotateNorm(XMQuaternionNormalize(axis), angle);
	}
	//--------------------------------------------------------------------------------------
	void Transform::RotateNorm(const DirectX::XMVECTOR& axis, float angle)
	{
		// ��]����p�̃N�H�[�^�j�I�����쐬
		XMVECTOR rotQuat = XMQuaternionRotationAxis(axis, angle);
		// �N�H�[�^�j�I�����m����Z
		m_Rotation = XMQuaternionNormalize(XMQuaternionMultiply(m_Rotation, rotQuat));
		MarkChanged();
	}

	//--------------------------------------------------------------------------------------
	void Transform::Scale(float mul)
	{
		m_Scale *= mul;
		MarkChanged();
	}
	//--------------------------------------------------------------------------------------
	void Transform::Scale(const DirectX::XMVECTOR& mul)
	{
		m_Scale *= mul;
		MarkChanged();
	}

	//--------------------------------------------------------------------------------------
	void Transform::Move(float forward, float right, float up)
	{
		// ���[�J�����W�n�ł̃x�N�g��
		auto local = XMVectorSet(right, up, forward, 0.0f);
		// ���[���h���W�n�ł̃x�N�g��
		auto world = XMVector3Rotate(local, m_Rotation);
		// �ړ�
		Translate(world);

	}

	//--------------------------------------------------------------------------------------
	void Transform::LookAtPosition(const DirectX::XMVECTOR& position)
	{
		//// ���݈ʒu����^�[�Q�b�g�ʒu�ւ̕����x�N�g��
		//XMVECTOR forword = XMVector3Normalize(position - m_Position);
		//// ���[���h���W�ł̐��ʕ����ւ̃x�N�g��
		//XMVECTOR def = XMVectorSet(0.0f, 1.0f, 0.0f, .0f);

		//m_Rotation = XMQuaternionNormalize(XMQuaternionRotationMatrix(
		//	XMMatrixLookToLH(m_Rotation, forword, def)
		//));

		// ���݈ʒu����^�[�Q�b�g�ʒu�ւ̕����x�N�g��
		XMVECTOR normDirection = XMVector3Normalize(position - m_Position);

		// ���ʕ����̃x�N�g���i+Z�Ƃ���j
		XMVECTOR pZ = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

		// ��]��
		XMVECTOR rotAxis = XMVector3Normalize(XMVector3Cross(pZ, normDirection));

		// �N�H�[�^�j�I���̌v�Z
		float dot = XMVectorGetX(XMVector3Dot(pZ, normDirection));
		float w = sqrtf((1.0f + dot) * 0.5f);	// w����
		float s = sqrtf((1.0f - dot) * 0.5f);	// ��]���ɑ΂���X�P�[��

		m_Rotation = XMVectorSet(
			XMVectorGetX(rotAxis) * s,
			XMVectorGetY(rotAxis) * s,
			XMVectorGetZ(rotAxis) * s,
			w
		);

		MarkChanged();
	}

	//--------------------------------------------------------------------------------------
	void Transform::MarkChanged()
	{
		m_IsChanged = true;

		for (auto& child : m_Children) {
			child->MarkChanged();
		}
	}


	//--------------------------------------------------------------------------------------
	void Transform::SetPosition(const DirectX::XMVECTOR& position)
	{
		m_Position = position;
		MarkChanged();
	}
	//--------------------------------------------------------------------------------------
	void Transform::SetPosition(float x, float y, float z)
	{
		SetPosition(XMVectorSet(x, y, z, 1.0f));
	}


	//--------------------------------------------------------------------------------------
	void Transform::SetRotation(const DirectX::XMVECTOR& rotation)
	{
		XMVECTOR norm = XMQuaternionNormalize(rotation);
		MarkChanged();
	}
	//--------------------------------------------------------------------------------------
	void Transform::SetRotation(float x, float y, float z, float w)
	{
		SetRotation(XMVectorSet(x, y, z, w));
	}


	//--------------------------------------------------------------------------------------
	void Transform::SetScele(const DirectX::XMVECTOR& scale)
	{
		m_Scale = scale;
		MarkChanged();
	}
	//--------------------------------------------------------------------------------------
	void Transform::SetScele(float x, float y, float z)
	{
		SetScele(XMVectorSet(x, y, z, 1.0f));
	}

	//--------------------------------------------------------------------------------------
	const DirectX::XMMATRIX& Transform::GetWorldMatrix()
	{
		if (m_IsChanged) {
			// ���̃R���|�[�l���g��world�s��
			auto localMatrix = XMMatrixScalingFromVector(m_Scale) *
				XMMatrixRotationQuaternion(m_Rotation) *
				XMMatrixTranslationFromVector(m_Position);

			// �e�Ɗ|�����킹��
			if (m_Parent != nullptr) {
				m_World = localMatrix * m_Parent->GetWorldMatrix();
			}
			else {
				m_World = localMatrix;
			}

			m_IsChanged = false;
		}
		return m_World;
	}

	//--------------------------------------------------------------------------------------
	void Transform::SetParent(Transform* parent)
	{
		if (m_Parent == parent)return;

		// ���ɐe���ݒ肳��Ă����ꍇ�폜
		if (m_Parent != nullptr) {
			auto& child = m_Parent->m_Children;
			child.erase(std::remove(child.begin(), child.end(), this), child.end());
		}

		// �e��ݒ�
		m_Parent = parent;

		// �e�̎q�����X�g�ɒǉ�
		if (m_Parent != nullptr) {
			m_Parent->AddChild(this);
		}

		MarkChanged();
	}

	//--------------------------------------------------------------------------------------
	void Transform::AddChild(Transform* child)
	{
		m_Children.push_back(child);
		child->SetParent(this);
	}
}