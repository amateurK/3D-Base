
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �X�L�j���O�A�j���[�V�������s�����b�V���f�[�^�N���X
// ���ۃN���X
// 
// �����	: amateurK
// �쐬��	: 2024/08/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "SkinningMesh.h" 


namespace Mesh {

	//--------------------------------------------------------------------------------------
	SkinningMesh::SkinningMesh()
		: Mesh()
	{
		m_SkinningData.clear();
		m_BoneData.clear();
		m_BoneDataHashmap.clear();
	}

	//--------------------------------------------------------------------------------------
	void SkinningMesh::UpdateBoneMatrices(std::vector<DirectX::XMMATRIX>& BoneMatrices)
	{
		CalcBoneMatrices(&m_BoneData[0], DirectX::XMMatrixIdentity(), BoneMatrices);
	}

	//--------------------------------------------------------------------------------------
	void SkinningMesh::CalcBoneMatrices(const BoneData* bone,
		const DirectX::XMMATRIX& parentMatrix,
		std::vector<DirectX::XMMATRIX>& BoneMatrices)
	{
		// �{�[���̍s����v�Z
		auto worldMatrix = parentMatrix * bone->InverseBindMatrix;
		// �{�[���̍s���z��Ɋi�[
		BoneMatrices[bone->ID] = worldMatrix;
		// �q�{�[���̍s����v�Z
		if (bone->FirstChild != nullptr) {
			CalcBoneMatrices(bone->FirstChild, worldMatrix, BoneMatrices);
		}
		// �Z��{�[���̍s����v�Z
		if (bone->NextSibling != nullptr) {
			CalcBoneMatrices(bone->NextSibling, parentMatrix, BoneMatrices);
		}
	}
}