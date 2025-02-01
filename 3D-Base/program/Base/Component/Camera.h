#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �J�������Ǘ�����R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2025/02/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component.h"

namespace AK_Base {

	/// @brief �J�������Ǘ�����R���|�[�l���g
	__declspec(align(16))
		class Camera : public Component
	{
	private:
		/// @brief �r���[�s��
		DirectX::XMMATRIX m_View;
		/// @brief �ˉe�s��
		DirectX::XMMATRIX m_Projection;

		/// @brief Transform�̍X�V��
		/// @details Transform���X�V����Ă��邩�𒲂ׂ�Ƃ��Ɏg�p
		uint32_t m_TransformChangedCount;

	public:
		/// @brief �R���X�g���N�^
		/// @param parent ���̃R���|�[�l���g�����L���Ă���Actor�iAddComponent<T>()�Œǉ������j
		Camera(Actor* const parent);
		/// @brief �f�X�g���N�^
		~Camera() = default;

		/// @brief �R���|�[�l���g�̖��O���擾
		/// @return ���O�̕�����
		inline virtual std::string GetName() const override { return "Camera"; }

		/// @brief �ˉe�s����Z�b�g
		/// @param angleY Y�����̎���i�p�x�j
		/// @param aspect �����_�[�^�[�Q�b�g�̃A�X�y�N�g��
		/// @param nearZ �r���[��Ԃ̑O��Z�l
		/// @param farZ �r���[��Ԃ̌��Z�l
		void SetScreen(const float angleY,
			const float aspect,
			const float nearZ = 0.01f,
			const float farZ = 100.0f);

		/// @brief �r���[�s����擾
		/// @return �r���[�s��̃|�C���^
		const DirectX::XMMATRIX* GetView();

		inline const DirectX::XMMATRIX* GetProjection() const { return &m_Projection; }

	};
}