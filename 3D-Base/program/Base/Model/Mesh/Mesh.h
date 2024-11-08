#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���b�V���f�[�^�N���X
// ���ۃN���X
// 
// �����	: amateurK
// �쐬��	: 2024/08/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../PictureResource.h" 

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

	/// @brief ���b�V���f�[�^
	struct MeshData
	{
		/// @brief ���_�̐�
		uint32_t NumVertex;
		/// @brief �ʂ̐�
		uint32_t NumFace;

		/// @brief �}�e���A���̐�
		uint32_t NumMaterial;

		//Mesh() {
		//	//ZeroMemory(this, sizeof(Mesh));
		//	// memo IndexBuffer���[���N���A���Ă���̂ŁAvector�����������Ȃ��Ƃ��߂���
		//	// vector��ZeroMemory()����ƃ��������[�N����������
		//	// �����炭�Avector�����̕ϐ��i�|�C���^�H�j�����āA���̃|�C���^�̐�̂��̂��폜����Ă��Ȃ�����H
		//}
		
		/// @brief �f�X�g���N�^
		~MeshData() = default;
	};

	/// @brief �}�e���A���f�[�^
	struct MaterialData
	{
		/// @brief ���̃}�e���A�����g�p���Ă���|���S���̒��_�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
		/// @brief ���̃}�e���A�����g�p���Ă���|���S���̃C���f�b�N�X�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer;
		/// @brief ���̃}�e���A�����g�p���Ă��钸�_�̐�
		uint32_t NumVertex;
		/// @brief ���̃}�e���A�����g�p���Ă���|���S����
		uint32_t NumFace;
		/// @brief �g�p����Ă���e�N�X�`��
		AK_Base::PictureResource Texture;

		/// @brief �f�X�g���N�^
		~MaterialData() 
		{
			IndexBuffer.Reset();
			VertexBuffer.Reset();
		}
	};

	/// @brief ���_�f�[�^
	struct SimpleVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
		XMFLOAT2 Texcoord;
	};



	/// @brief �V���v���ȗ����̂̃��b�V���f�[�^
	__declspec(align(16))
		class Mesh
	{
	protected:

		/// @brief ���b�V���f�[�^
		std::unique_ptr<MeshData> m_Mesh;
		/// @brief �}�e���A��
		std::vector<MaterialData> m_Material;

		///// @brief �C���f�b�N�X�o�b�t�@�i���f�[�^�j
		//int* m_IndexBuffer;
		///// @brief ���_�o�b�t�@�i���f�[�^�j
		//SimpleVertex* m_VertexBuffer;

	public:
		/// @brief �R���X�g���N�^
		Mesh();
		/// @brief �f�X�g���N�^
		virtual ~Mesh();

		/// @brief ���b�V�����쐬
		/// @param device �f�o�C�X�ւ̃|�C���^
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @return ����ɍ쐬�ł�����
		virtual HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			std::wstring fileName = L"") = 0;

		/// @brief ���b�V���̉��
		void DestroyMesh();

		/// @brief ���b�V�����g���ĕ`�悷��
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param customFunction �`��O�̔C�ӂ̏����i��ɃV�F�[�_�[�j
		/// @param textureSlot �V�F�[�_�[�̃e�N�X�`���X���b�gID
		virtual void Render(ID3D11DeviceContext* const context,
			std::function<void(int, const std::vector<MaterialData>)> customFunction = nullptr,
			const UINT textureSlot = 0);

		/// @brief �}�e���A�����w�肵�ĕ`��
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param id �}�e���A����ID
		/// @param testureSlot �V�F�[�_�[�̃e�N�X�`���X���b�gID
		virtual void DrawSubset(ID3D11DeviceContext* const context, const int id, const UINT testureSlot = 0) = 0;


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Mesh));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}
