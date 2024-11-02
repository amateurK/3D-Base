
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �f�o�b�O�p�̃J�������Ǘ�����N���X
// ���R�ɓ�����
// 
// �����	: amateurK
// �쐬��	: 2024/11/01
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
		// �㉺�ړ��͓Ɨ�
		auto y = up;

		// �J�����̌����Ă���������Z�o
		auto vec = m_VectorAt - m_VectorEye;
		float rad = atan2f(vec.m128_f32[0], vec.m128_f32[2]);

		// TODO : �e�[�u����
		// �p�x�����Ɉړ��ʂ�����
		auto x = sin(rad) * front + cos(rad) * right;
		auto z = cos(rad) * front - sin(rad) * right;

		MoveWithAxis(x, y, z);
	}

	//---------------------------------------------------------------------------------------------
	void DebugCamera::MoveWithAxis(float x, float y, float z)
	{
		// �J�����̏ꏊ���X�V
		m_VectorEye.m128_f32[0] += x;
		m_VectorEye.m128_f32[1] += y;
		m_VectorEye.m128_f32[2] += z;

		m_VectorAt.m128_f32[0] += x;
		m_VectorAt.m128_f32[1] += y;
		m_VectorAt.m128_f32[2] += z;


		UpdateViewMatrix();
	}
}