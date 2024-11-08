
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// メッシュデータクラス
// 抽象クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/08/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h"

namespace Mesh {

	//--------------------------------------------------------------------------------------
	Mesh::Mesh()
	{
		m_Mesh.clear();
	}

	//--------------------------------------------------------------------------------------
	Mesh::~Mesh()
	{
		DestroyMesh();
	}

	//--------------------------------------------------------------------------------------
	void Mesh::DestroyMesh()
	{
		m_Mesh.clear();
	}

	//--------------------------------------------------------------------------------------
	void Mesh::Render(ID3D11DeviceContext* const context,
		std::function<void(int, const std::vector<MeshData>)> customFunction,
		const UINT textureSlot)
	{
		// 各マテリアルごとに描画する
		for (uint32_t materialID = 0; materialID < m_Mesh.size(); materialID++)
		{
			if (customFunction) {
				customFunction(materialID, m_Mesh);
			}

			DrawSubset(context, materialID, textureSlot);
		}
	}

}