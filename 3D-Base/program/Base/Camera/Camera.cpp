
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// カメラの役割を担う
// Shaderに渡すビュー行列、射影行列もここで管理する
// 
// 製作者	: amateurK
// 作成日	: 2024/07/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Camera.h"


namespace Camera {

	Camera::Camera()
		: m_View(XMMatrixIdentity())
		, m_Projection(XMMatrixIdentity())
	{

	}

	//--------------------------------------------------------------------------------------
	void Camera::SetCamera(const DirectX::XMVECTOR* eye, const DirectX::XMVECTOR* at, const DirectX::XMVECTOR* up)
	{
		// eye と at の x,y,z の値が同じだった場合エラーになるので注意
		if(eye != nullptr)m_VectorEye = *eye;
		if(at != nullptr)m_VectorAt = *at;
		if(up != nullptr)m_VectorUp = *up;

		UpdateViewMatrix();
	}

	//--------------------------------------------------------------------------------------
	void Camera::SetScreen(const float angleY, const float aspect, const float nearZ, const float farZ)
	{
		m_Projection = XMMatrixPerspectiveFovLH(angleY, aspect, nearZ, farZ);
	}

	//--------------------------------------------------------------------------------------
	void Camera::MoveCamera(const DirectX::XMMATRIX& matrix)
	{
		m_View = matrix * m_View;
	}
	//---------------------------------------------------------------------------------------------
	void Camera::UpdateViewMatrix()
	{
		m_View = XMMatrixLookAtLH(m_VectorEye, m_VectorAt, m_VectorUp);
	}
}