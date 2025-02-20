#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �X�L�j���O�A�j���[�V�������s�����b�V���f�[�^�N���X
// ���ۃN���X
// 
// �����	: amateurK
// �쐬��	: 2025/02/08
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h" 

namespace Mesh {

	/// @brief �X�L�j���O�A�j���[�V�����Ɏg�p����f�[�^
	struct SkinningData
	{
		/// @brief �e���_���e�����󂯂�{�[��
		std::vector<std::array<uint8_t, 4>> BoneIndices;
		/// @brief �e�����󂯂�{�[���̏d��
		std::vector<std::array<float, 4>> BoneWeights;
	};

	/// @brief �{�[���f�[�^
	struct BoneData
	{
		/// @brief �{�[��id
		int ID;
		/// @brief �{�[����
		std::string Name;
		/// @brief ������Ԃł̋t�o�C���h�s��
		DirectX::XMMATRIX InverseBindMatrix;
		/// @brief ���[�J���ϊ��s��
		DirectX::XMMATRIX LocalMatrix;
		/// @brief 1�Ԗڂ̎q�{�[��
		BoneData* FirstChild;
		/// @brief ���̌Z��{�[��
		BoneData* NextSibling;
	};

	/// @brief ���_�f�[�^
	struct SkinningVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 Texcoord;
		uint8_t BoneIndices[4];
		DirectX::XMFLOAT4 BoneWeight;
	};

	/// @brief �X�L�j���O�A�j���[�V�������s�����b�V���f�[�^
	__declspec(align(16))
	class SkinningMesh : public Mesh
	{
	protected:
		/// @brief �X�L�j���O�A�j���[�V�����Ɏg�p����f�[�^
		/// @details Mesh�N���X��m_Mesh�ɑΉ�
		std::vector<SkinningData> m_SkinningData;

		/// @brief �{�[���f�[�^
		/// @details index��Bone��id�ƑΉ����Ă���
		std::vector<BoneData> m_BoneData;

		/// @brief �{�[���f�[�^�𕶎���Ō������邽�߂̃n�b�V���}�b�v
		/// @details �L�[ : �{�[����
		/// @details �l�@ : SkinningData�̃C���f�b�N�X
		std::unordered_map<std::string, BoneData*> m_BoneDataHashmap;

	public:
		/// @brief �R���X�g���N�^
		SkinningMesh();
		/// @brief �f�X�g���N�^
		virtual ~SkinningMesh() = default;

		/// @brief ���b�V�����쐬
		/// @param device �f�o�C�X�ւ̃|�C���^
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param settings �C���|�[�g���̃p�����[�^
		/// @return ����ɍ쐬�ł�����
		virtual HRESULT CreateMesh(ID3D11Device* const device,
			ID3D11DeviceContext* const context,
			std::wstring fileName = L"",
			ImportSettings* settings = nullptr) override = 0;

		/// @brief �}�e���A�����w�肵�ĕ`��
		/// @param context �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
		/// @param id �}�e���A����ID
		/// @param textureSlot �V�F�[�_�[�̃e�N�X�`���X���b�gID
		virtual void DrawSubset(ID3D11DeviceContext* const context,
			const int id, const UINT textureSlot = 0) override = 0;



		/// @brief �{�[���̔z���n��
		inline const std::vector<BoneData>& GetBoneData() const { return m_BoneData; }

		/// @brief �{�[���̐���Ԃ�
		inline size_t GetBoneDataSize() const { return m_BoneData.size(); }
	};
}