
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// スキニングアニメーションを行うメッシュデータクラス
// 抽象クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/08/01
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
		// ボーンの行列を計算
		auto worldMatrix = parentMatrix * bone->InverseBindMatrix;
		// ボーンの行列を配列に格納
		BoneMatrices[bone->ID] = worldMatrix;
		// 子ボーンの行列を計算
		if (bone->FirstChild != nullptr) {
			CalcBoneMatrices(bone->FirstChild, worldMatrix, BoneMatrices);
		}
		// 兄弟ボーンの行列を計算
		if (bone->NextSibling != nullptr) {
			CalcBoneMatrices(bone->NextSibling, parentMatrix, BoneMatrices);
		}
	}
}