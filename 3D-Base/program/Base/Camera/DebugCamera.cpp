
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// デバッグ用のカメラを管理するクラス
// 自由に動ける
// 
// 製作者	: amateurK
// 作成日	: 2024/11/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "DebugCamera.h"

namespace Camera {
	//---------------------------------------------------------------------------------------------
	DebugCamera::DebugCamera()
	{

	}
	//---------------------------------------------------------------------------------------------
	DebugCamera::~DebugCamera()
	{

	}

	//---------------------------------------------------------------------------------------------
	void DebugCamera::MoveWithViewpoint(float front, float right, float up)
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
	void DebugCamera::MoveWithAxis(float x, float y, float z)
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
}