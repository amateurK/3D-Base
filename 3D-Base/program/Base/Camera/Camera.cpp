
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �J�����̖�����S��
// Shader�ɓn���r���[�s��A�ˉe�s��������ŊǗ�����
// 
// �����	: amateurK
// �쐬��	: 2024/07/30
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
		// eye �� at �� x,y,z �̒l�������������ꍇ�G���[�ɂȂ�̂Œ���
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