#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ��(piece)�̃N���X
// 
// �����	: amateurK
// �쐬��	: 2024/04/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Base/Model/ModelActor.h"

namespace Piece {

	/// @brief ��(piece)
	__declspec(align(16))
		class Piece : public AK_Base::ModelActor
	{
	protected:
		/// @brief ��̉��l
		int m_Value;

	public:
		/// @brief �R���X�g���N�^
		/// @param name : ���ʖ�
		/// @param status : �������
		Piece(
			Shader::Shader* const shader
			, std::wstring name = L"unnamed"
			, std::wstring fileName = L""
		);

		/// @brief �f�X�g���N�^
		virtual ~Piece();


		/// @brief �X�V
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Move()����̌o�ߎ��ԁi�b�j
		virtual void Move(const double& totalTime, const float& elapsedTime) override;
		/// @brief �`��
		/// @param totalTime : �A�v���P�[�V�����N������̌o�ߎ��ԁi�b�j
		/// @param elapsedTime : �O���Render()����̌o�ߎ��ԁi�b�j
		virtual void Render(const double& totalTime, const float& elapsedTime) override;

		/// @brief ���W���Z�b�g����
		/// @param pos3 ���W
		inline void SetPosition(DirectX::XMFLOAT3A pos3)
		{
			m_Position = pos3;
		}
		/// @brief ���W���Z�b�g����
		/// @param x ���Wx
		/// @param y ���Wy
		/// @param z ���Wz
		inline void SetPosition(float x, float y, float z)
		{
			m_Position = DirectX::XMFLOAT3A(x, y, z);
		}

		/// @brief �T�C�Y�̕ύX
		/// @param x x������
		/// @param y y������
		/// @param z z������
		inline void Scaling(float x, float y, float z)
		{
			m_Scale = DirectX::XMFLOAT3A(x, y, z);
		}
		/// @brief �T�C�Y�̕ύX
		/// @param �{��
		inline void Scaling(float scale)
		{
			m_Scale = DirectX::XMFLOAT3A(scale, scale, scale);
		}

		// �ړ��\�ȏꏊ��Ԃ�

		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Piece));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}

