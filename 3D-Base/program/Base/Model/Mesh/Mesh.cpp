
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���b�V���f�[�^�N���X
// ���ۃN���X
// 
// �����	: amateurK
// �쐬��	: 2024/08/01
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
		// �e�}�e���A�����Ƃɕ`�悷��
		for (uint32_t materialID = 0; materialID < m_Mesh.size(); materialID++)
		{
			if (customFunction) {
				customFunction(materialID, m_Mesh);
			}

			DrawSubset(context, materialID, textureSlot);
		}
	}

}