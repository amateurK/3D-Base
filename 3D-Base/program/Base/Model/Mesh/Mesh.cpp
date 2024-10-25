
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
		: m_Mesh(nullptr)
	{
		m_Material.clear();
	}

	//--------------------------------------------------------------------------------------
	Mesh::~Mesh()
	{
		DestroyMesh();
	}

	//--------------------------------------------------------------------------------------
	void Mesh::DestroyMesh()
	{
		m_Mesh.reset();
		m_Material.clear();
	}

	//--------------------------------------------------------------------------------------
	void Mesh::Render(ID3D11DeviceContext* const context,
		std::function<void(int, const std::vector<MaterialData>)> customFunction,
		const UINT textureSlot)
	{
		// 各マテリアルごとに描画する
		for (uint32_t materialID = 0; materialID < m_Mesh->NumMaterial; materialID++)
		{
			if (customFunction) {
				customFunction(materialID, m_Material);
			}

			DrawSubset(context, materialID, textureSlot);
		}
	}

}