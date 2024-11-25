
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 中心座標、回転、スケールを保持するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2024/11/18
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
		// 回転する用のクォータニオンを作成
		XMVECTOR rotQuat = XMQuaternionRotationAxis(axis, angle);
		// クォータニオン同士を乗算
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
		Translate(XMVector3Rotate(XMVectorSet(right, up, forward, 0.0f), m_Rotation));
	}

	//--------------------------------------------------------------------------------------
	void Transform::LookAt(DirectX::XMVECTOR& position)
	{
		// 現在位置からターゲット位置への方向ベクトル
		XMVECTOR forword = XMVector3Normalize(position - m_Position);
		// ワールド座標での正面方向へのベクトル
		XMVECTOR def = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

		m_Rotation = XMQuaternionNormalize(XMQuaternionRotationMatrix(
			XMMatrixLookToLH(m_Rotation, forword, def)
		));
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
		m_Position.m128_f32[0] = x;
		m_Position.m128_f32[1] = y;
		m_Position.m128_f32[2] = z;
		MarkChanged();
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
		m_Scale.m128_f32[0] = x;
		m_Scale.m128_f32[1] = y;
		m_Scale.m128_f32[2] = z;
		MarkChanged();
	}

	//--------------------------------------------------------------------------------------
	const DirectX::XMMATRIX& Transform::GetWorldMatrix()
	{
		if (m_IsChanged) {
			// このコンポーネントのworld行列
			auto localMatrix = XMMatrixScalingFromVector(m_Scale) *
				XMMatrixRotationQuaternion(m_Rotation) *
				XMMatrixTranslationFromVector(m_Position);

			// 親と掛け合わせる
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

		// 既に親が設定されていた場合削除
		if (m_Parent != nullptr) {
			auto& child = m_Parent->m_Children;
			child.erase(std::remove(child.begin(), child.end(), this), child.end());
		}

		// 親を設定
		m_Parent = parent;

		// 親の子供リストに追加
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