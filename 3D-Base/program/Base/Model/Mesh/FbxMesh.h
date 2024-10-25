#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// FBX�t�@�C������ǂݍ��ރ��b�V���f�[�^
// 
// �����	: amateurK
// �쐬��	: 2024/08/05
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h"

namespace Mesh {

	/// @brief �V���v���ȗ����̂̃��b�V���f�[�^
	__declspec(align(16))
		class FbxMesh
		: public Mesh
	{
	private:



	public:
		/// @brief �R���X�g���N�^
		FbxMesh();
		/// @brief �f�X�g���N�^
		virtual ~FbxMesh();

		/// @brief ���b�V���̉��
		void DestroyMesh();

		/// @brief ���b�V�����쐬
		/// @param device �f�o�C�X�ւ̃|�C���^
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param fileName FBX�t�@�C����
		/// @return ����ɍ쐬�ł�����
		virtual HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			const std::wstring fileName = L"") override;

		/// @brief �}�e���A�����w�肵�ĕ`��
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param id �}�e���A����ID
		/// @param testureSlot �V�F�[�_�[�̃e�N�X�`���X���b�gID
		virtual void DrawSubset(ID3D11DeviceContext* const context, const int id, const UINT testureSlot = 0);


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(FbxMesh));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}
