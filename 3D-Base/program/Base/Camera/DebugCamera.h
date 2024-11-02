#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �f�o�b�O�p�̃J�������Ǘ�����N���X
// ���R�ɓ�����
// 
// �����	: amateurK
// �쐬��	: 2024/11/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Camera.h"

namespace Camera {

	__declspec(align(16))
		class DebugCamera : public Camera
	{
	private:

	public:
		/// @brief �R���X�g���N�^
		DebugCamera();
		/// @brief �f�X�g���N�^
		~DebugCamera();

		/// @brief ���_����ɃJ�������ړ�������
		/// @param front �O�������ւ̈ړ��x�N�g��
		/// @param right �E�����ւ̈ړ��x�N�g��
		/// @param up ������ւ̈ړ��x�N�g��
		void MoveWithViewpoint(float front, float right, float up);

		/// @brief ���_����ɃJ�������ړ�������
		/// @param x x���W�ւ̈ړ��x�N�g��
		/// @param y y���W�ւ̈ړ��x�N�g��
		/// @param z z���W�ւ̈ړ��x�N�g��
		void MoveWithAxis(float x, float y, float z);

		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(DebugCamera));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}