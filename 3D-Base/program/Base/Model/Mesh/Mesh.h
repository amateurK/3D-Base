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

	/// @brief �}�e���A���f�[�^
	struct MeshData
	{
		/// @brief ���̃}�e���A�����g�p���Ă���|���S���̒��_�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
		/// @brief ���̃}�e���A�����g�p���Ă���|���S���̃C���f�b�N�X�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer;
		/// @brief ���̃}�e���A�����g�p���Ă��钸�_�̐�
		uint32_t NumVertex;
		/// @brief ���̃}�e���A�����g�p���Ă���|���S����
		uint32_t NumFace;
		/// @brief �g�p����Ă���e�N�X�`���̃��\�[�X�r���[�ւ̃|�C���^
		ID3D11ShaderResourceView** SRView;
		/// @brief �C���f�b�N�X�o�b�t�@��1�f�[�^�̃T�C�Y
		DXGI_FORMAT DXGI_Format;

		/// @brief �f�X�g���N�^
		~MeshData() 
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
		std::vector<MeshData> m_Mesh;
		/// @brief �e�N�X�`���f�[�^
		std::vector<AK_Base::PictureResource> m_Texture;

	public:
		/// @brief �R���X�g���N�^
		Mesh();
		/// @brief �f�X�g���N�^
		virtual ~Mesh();

		/// @brief ���b�V�����쐬
		/// @param device �f�o�C�X�ւ̃|�C���^
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param settings �C���|�[�g���̃p�����[�^
		/// @return ����ɍ쐬�ł�����
		virtual HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			std::wstring fileName = L"",
			ImportSettings* settings = nullptr) = 0;

		/// @brief ���b�V���̉��
		void DestroyMesh();

		/// @brief ���b�V�����g���ĕ`�悷��
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param customFunction �`��O�̔C�ӂ̏����i��ɃV�F�[�_�[�j
		/// @param textureSlot �V�F�[�_�[�̃e�N�X�`���X���b�gID
		virtual void Render(ID3D11DeviceContext* const context,
			std::function<void(int, const std::vector<MeshData>)> customFunction = nullptr,
			const UINT textureSlot = 0);

		/// @brief �}�e���A�����w�肵�ĕ`��
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param id �}�e���A����ID
		/// @param textureSlot �V�F�[�_�[�̃e�N�X�`���X���b�gID
		virtual void DrawSubset(ID3D11DeviceContext* const context,
			const int id, const UINT textureSlot = 0) = 0;


		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Mesh));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}
