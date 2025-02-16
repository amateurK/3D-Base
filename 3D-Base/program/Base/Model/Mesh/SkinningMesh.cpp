
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
		// �ꎞ�I�Ƀ��[���h�ϊ��s���u���Ă����ꏊ���m��
		std::vector<DirectX::XMMATRIX> worldMatrices(m_BoneData.size());

		// �{�[���̍s����X�V
		CalcBoneMatrices(&m_BoneData[0], DirectX::XMMatrixIdentity(), BoneMatrices, worldMatrices);
	}

	//--------------------------------------------------------------------------------------
	void SkinningMesh::CalcBoneMatrices(const BoneData* bone,
		const DirectX::XMMATRIX& parentMatrix,
		std::vector<DirectX::XMMATRIX>& BoneMatrices,
		std::vector<DirectX::XMMATRIX>& worldMatrices)
	{
		// �{�[���̃��[���h�ϊ��s����v�Z
		auto worldMatrix = parentMatrix * bone->LocalMatrix;

		// �����ɃA�j���[�V����������ǉ��I
		//if (bone->ID == 30) {
		//	worldMatrix *= DirectX::XMMatrixRotationY(1.0f);
		//}


		// �{�[���̃��[���h�ϊ��s���z��Ɋi�[
		worldMatrices[bone->ID] = worldMatrix;
		// �{�[���̍ŏI�s���z��Ɋi�[
		BoneMatrices[bone->ID] = worldMatrix * bone->InverseBindMatrix;

		// �q�{�[���̍s����v�Z
		if (bone->FirstChild != nullptr) {
			CalcBoneMatrices(bone->FirstChild, worldMatrix, BoneMatrices, worldMatrices);
		}
		// �Z��{�[���̍s����v�Z
		if (bone->NextSibling != nullptr) {
			CalcBoneMatrices(bone->NextSibling, parentMatrix, BoneMatrices, worldMatrices);
		}
	}
}