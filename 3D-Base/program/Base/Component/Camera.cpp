
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// カメラを管理するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2025/02/01
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
			// カメラの回転を取得
			DirectX::XMVECTOR rotation = m_ParentActor->GetTransform()->GetRotation();

			// カメラの向き（正面方向、上方向）を計算
			DirectX::XMVECTOR forward = XMVector3Rotate({ 0.0f, 0.0f, 1.0f, 0.0f }, rotation);
			DirectX::XMVECTOR up = XMVector3Rotate({ 0.0f, 1.0f, 0.0f, 0.0f }, rotation);

			// ビュー行列を計算
			m_View = XMMatrixLookToLH(m_ParentActor->GetTransform()->GetPosition(), forward, up);

			// 更新回数を記録
			m_TransformChangedCount = m_ParentActor->GetTransform()->GetChengedCount();
		}

		return &m_View;
	}
}