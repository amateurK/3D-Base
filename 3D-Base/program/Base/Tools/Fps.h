#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// FPS���v������N���X
// ��莞�Ԃ��ƂɎ����l�͍X�V�����
// 
// �����	: amateurK
// �쐬��	: 2025/05/22
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace Tools {
	class Fps
	{
	private:
		/// @brief Fps�����l
		uint16_t m_Fps;
		/// @brief ���莞�̃J�E���^�[
		uint16_t m_Count;
		/// @brief ���莞�̊J�n����̎���
		float m_TotalTime;

	public:
		/// @brief �R���X�g���N�^
		Fps()
			: m_Fps(0)
			, m_Count(0)
			, m_TotalTime(0.0f)
		{}

		/// @brief �f�X�g���N�^
		~Fps() = default;

		/// @brief ���t���[�����s
		inline void Update(const float elapsedTime)
		{
			m_TotalTime += elapsedTime;
			m_Count++;
			// ��莞�Ԍo�߂��Ă���������l���X�V
			if (m_TotalTime >= 1.0f) {
				m_Fps = m_Count;
				m_Count = 0;
				m_TotalTime -= 1.0f;
			}
		}

		/// @brief Fps���擾
		/// @return Fps�̎����l
		int GetFps() const
		{
			return m_Fps;
		}
	};
}

