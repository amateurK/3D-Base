
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

	//---------------------------------------------------------------------------------------------
	void Camera::MoveWithViewpoint(float front, float right, float up)
	{
		// 上下移動は独立
		auto y = up;

		// カメラの向いている向きを算出
		auto vec = m_VectorAt - m_VectorEye;
		float rad = atan2f(vec.m128_f32[0], vec.m128_f32[2]);

		// TODO : テーブル化
		// 角度を元に移動量を決定
		auto x = sin(rad) * front + cos(rad) * right;
		auto z = cos(rad) * front - sin(rad) * right;

		MoveWithAxis(x, y, z);
	}

	//---------------------------------------------------------------------------------------------
	void Camera::MoveWithAxis(float x, float y, float z)
	{
		// カメラの場所を更新
		m_VectorEye.m128_f32[0] += x;
		m_VectorEye.m128_f32[1] += y;
		m_VectorEye.m128_f32[2] += z;

		m_VectorAt.m128_f32[0] += x;
		m_VectorAt.m128_f32[1] += y;
		m_VectorAt.m128_f32[2] += z;


		UpdateViewMatrix();
	}

	//---------------------------------------------------------------------------------------------
	void Camera::UpdateViewMatrix()
	{
		m_View = XMMatrixLookAtLH(m_VectorEye, m_VectorAt, m_VectorUp);
	}
}