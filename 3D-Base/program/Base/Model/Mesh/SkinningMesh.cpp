
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
		// 一時的にワールド変換行列を置いておく場所を確保
		std::vector<DirectX::XMMATRIX> worldMatrices(m_BoneData.size());

		// ボーンの行列を更新
		CalcBoneMatrices(&m_BoneData[0], DirectX::XMMatrixIdentity(), BoneMatrices, worldMatrices);
	}

	//--------------------------------------------------------------------------------------
	void SkinningMesh::CalcBoneMatrices(const BoneData* bone,
		const DirectX::XMMATRIX& parentMatrix,
		std::vector<DirectX::XMMATRIX>& BoneMatrices,
		std::vector<DirectX::XMMATRIX>& worldMatrices)
	{
		// ボーンのワールド変換行列を計算
		auto worldMatrix = parentMatrix * bone->LocalMatrix;

		// ここにアニメーション処理を追加！
		//if (bone->ID == 30) {
		//	worldMatrix *= DirectX::XMMatrixRotationY(1.0f);
		//}


		// ボーンのワールド変換行列を配列に格納
		worldMatrices[bone->ID] = worldMatrix;
		// ボーンの最終行列を配列に格納
		BoneMatrices[bone->ID] = worldMatrix * bone->InverseBindMatrix;

		// 子ボーンの行列を計算
		if (bone->FirstChild != nullptr) {
			CalcBoneMatrices(bone->FirstChild, worldMatrix, BoneMatrices, worldMatrices);
		}
		// 兄弟ボーンの行列を計算
		if (bone->NextSibling != nullptr) {
			CalcBoneMatrices(bone->NextSibling, parentMatrix, BoneMatrices, worldMatrices);
		}
	}
}