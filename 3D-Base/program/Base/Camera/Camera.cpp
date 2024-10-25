
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
	void Camera::SetCamera(const DirectX::XMVECTOR& eye, const DirectX::XMVECTOR& at, const DirectX::XMVECTOR& up)
	{
		// eye �� at �� x,y,z �̒l�������������ꍇ�G���[�ɂȂ�̂Œ���
		m_View = XMMatrixLookAtLH(eye, at, up);
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
}