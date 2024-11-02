#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// FBX�t�@�C������ǂݍ��ރ��b�V���f�[�^
// 
// Assimp_native_4.1_v142���g�p
// �c�[�� -> NuGet�p�b�P�[�W�}�l�[�W�� -> �\�����[�V������NuGet�p�b�P�[�W�̊Ǘ�
//   ����p�b�P�[�W�\�[�X��nuget.org�̏�ԂŌ�����������Əo�Ă���
// Assimp�ɂ���ނ����낢�날��H�ǂꂪ�����̂��͕s��
// �ǉ��̃C���N���[�h�f�B���N�g���Ɉȉ���ǉ�����ƕ֗�
// �@$(SolutionDir)packages\Assimp_native_4.1_v142.4.1.0\build\native\include
// �v���p�e�B -> �r���h�C�x���g -> �r���h��̃C�x���g�ɂ������͂����dll��������exe�̉��ɒu���Ă����
//   xcopy /Y "$(SolutionDir)packages\Assimp_native_4.1_v142.4.1.0\build\native\lib\x64-Debug\*.dll" "$(OutDir)"
// 
// 
// �����	: amateurK
// �쐬��	: 2024/08/05
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h"


namespace Mesh {

	/// @brief �C���|�[�g���̃p�����[�^
	struct ImportSettings
	{
		/// @brief U���W�𔽓]�����邩
		bool InverseU = false;
		/// @brief V���W�𔽓]�����邩
		bool InverseV = false;

		ImportSettings(bool invU = false, bool invV = false)
			: InverseU(invU)
			, InverseV(invV)
		{}
	};

	/// @brief �V���v���ȗ����̂̃��b�V���f�[�^
	__declspec(align(16))
		class FbxMesh : public Mesh
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
		/// @brief ���b�V�����쐬
		/// @param device �f�o�C�X�ւ̃|�C���^
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param fileName FBX�t�@�C����
		/// @param settings �C���|�[�g���̃p�����[�^
		/// @return ����ɍ쐬�ł�����
		HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			const std::wstring fileName = L"",
			ImportSettings* settings = nullptr
			);

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
