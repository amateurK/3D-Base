#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �V���v���ȗ����̂̃��b�V���f�[�^
// 
// �����	: amateurK
// �쐬��	: 2024/07/26
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h"

namespace Mesh {

	/// @brief �V���v���ȗ����̂̃��b�V���f�[�^
	__declspec(align(16))
		class BasicMesh
		: public Mesh
	{
	private:


	public:
		/// @brief �R���X�g���N�^
		BasicMesh();
		/// @brief �f�X�g���N�^
		virtual ~BasicMesh() = default;

		/// @brief ���b�V�����쐬
		/// @param device �f�o�C�X�ւ̃|�C���^
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @return ����ɍ쐬�ł�����
		/// @details �t�@�C������ǂݍ��ޏꍇ�̓I�[�o�[���[�h���č��
		virtual HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			std::wstring fileName = L"") override;

		/// @brief �}�e���A�����w�肵�ĕ`��
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param id �}�e���A����ID
		/// @param testureSlot �V�F�[�_�[�̃e�N�X�`���X���b�gID
		virtual void DrawSubset(ID3D11DeviceContext* const context, const int id, const UINT testureSlot = 0);


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(BasicMesh));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}