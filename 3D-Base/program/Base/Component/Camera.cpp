
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �J�������Ǘ�����R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2025/02/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Camera.h"
#include "Transform.h"


using namespace DirectX;

namespace AK_Base {

	Camera::Camera(Actor* const parent)
		: Component(parent)
		, m_View(DirectX::XMMatrixIdentity())
		, m_Projection(DirectX::XMMatrixIdentity())
		, m_TransformChangedCount(0)
	{
	}

	//--------------------------------------------------------------------------------------
	void Camera::SetScreen(const float angleY, const float aspect, const float nearZ, const float farZ)
	{
		m_Projection = XMMatrixPerspectiveFovLH(angleY, aspect, nearZ, farZ);
	}

	//--------------------------------------------------------------------------------------
	const DirectX::XMMATRIX* Camera::GetView()
	{
		if (m_TransformChangedCount != m_ParentActor->GetTransform()->GetChengedCount()) 
		{
			// �J�����̉�]���擾
			DirectX::XMVECTOR rotation = m_ParentActor->GetTransform()->GetRotation();

			// �J�����̌����i���ʕ����A������j���v�Z
			DirectX::XMVECTOR forward = XMVector3Rotate({ 0.0f, 0.0f, 1.0f, 0.0f }, rotation);
			DirectX::XMVECTOR up = XMVector3Rotate({ 0.0f, 1.0f, 0.0f, 0.0f }, rotation);

			// �r���[�s����v�Z
			m_View = XMMatrixLookToLH(m_ParentActor->GetTransform()->GetPosition(), forward, up);

			// �X�V�񐔂��L�^
			m_TransformChangedCount = m_ParentActor->GetTransform()->GetChengedCount();
		}

		return &m_View;
	}
}