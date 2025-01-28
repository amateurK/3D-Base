#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �����̃��b�V���f�[�^
// 
// �����	: amateurK
// �쐬��	: 2025/01/27
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h"

namespace Mesh {

	/// @brief VRM�t�@�C������ǂݍ��񂾃��b�V�����Ǘ�����N���X
	__declspec(align(16))
		class LineMesh : public Mesh
	{
	private:



	public:
		/// @brief �R���X�g���N�^
		LineMesh();
		/// @brief �f�X�g���N�^
		virtual ~LineMesh();

		/// @brief ���b�V�����쐬
		/// @param device �f�o�C�X�ւ̃|�C���^
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param fileName �s�v
		/// @param settings �C���|�[�g���̃p�����[�^
		/// @return ����ɍ쐬�ł�����
		virtual HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			const std::wstring fileName = L"",
			ImportSettings* settings = nullptr
		) override;

		/// @brief �}�e���A�����w�肵�ĕ`��
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param id �}�e���A����ID
		/// @param testureSlot �V�F�[�_�[�̃e�N�X�`���X���b�gID
		virtual void DrawSubset(ID3D11DeviceContext* const context, const int id, const UINT testureSlot = 0);


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(LineMesh));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}
