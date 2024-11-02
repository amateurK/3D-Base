#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �J�����̖�����S��
// Shader�ɓn���r���[�s��A�ˉe�s��������ŊǗ�����
// 
// �����	: amateurK
// �쐬��	: 2024/07/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace Camera {

	__declspec(align(16))
		class Camera
	{
	protected:
		/// @brief �r���[�s��
		DirectX::XMMATRIX m_View;
		/// @brief �ˉe�s��
		DirectX::XMMATRIX m_Projection;

		/// @brief �J�����̈ʒu
		DirectX::XMVECTOR m_VectorEye;
		/// @brief �J�����̒����_
		DirectX::XMVECTOR m_VectorAt;
		/// @brief �J�����̏�����x�N�g��
		DirectX::XMVECTOR m_VectorUp;

	public:
		/// @brief �R���X�g���N�^
		Camera();
		/// @brief �f�X�g���N�^
		~Camera() = default;

		/// @brief �r���[�s��(�J����)���Z�b�g
		/// @details nullptr������Ƃ��̕����͖�������
		/// @param eye �J�����̈ʒu
		/// @param at �J�����̒����_
		/// @param up �J�����̏�����x�N�g��
		void SetCamera(const DirectX::XMVECTOR* eye = nullptr,
			const DirectX::XMVECTOR* at = nullptr,
			const DirectX::XMVECTOR* up = nullptr);


		/// @brief �ˉe�s����Z�b�g
		/// @param angleY Y�����̎���i�p�x�j
		/// @param aspect �����_�[�^�[�Q�b�g�̃A�X�y�N�g��
		/// @param nearZ �r���[��Ԃ̑O��Z�l
		/// @param farZ �r���[��Ԃ̌��Z�l
		void SetScreen(const float angleY,
			const float aspect,
			const float nearZ = 0.01f,
			const float farZ = 100.0f);

		/// @brief �J�������ړ�������
		/// @param matrix �r���[�s���������s��
		void MoveCamera(const DirectX::XMMATRIX& matrix);

		/// @brief View�s����X�V
		inline void UpdateViewMatrix();

		inline DirectX::XMMATRIX GetView() const { return m_View; }
		inline DirectX::XMMATRIX GetProjection() const { return m_Projection; }


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Camera));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}