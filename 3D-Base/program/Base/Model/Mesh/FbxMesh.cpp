
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// FBXファイルから読み込むメッシュデータ
// 
// 製作者	: amateurK
// 作成日	: 2024/08/05
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "FbxMesh.h"

namespace Mesh {

	FbxMesh::FbxMesh()
	{

	}

	//--------------------------------------------------------------------------------------
	FbxMesh::~FbxMesh()
	{
		DestroyMesh();
	}

	//--------------------------------------------------------------------------------------
	void FbxMesh::DestroyMesh()
	{

	}

	//--------------------------------------------------------------------------------------
	HRESULT FbxMesh::CreateMesh(ID3D11Device* const device,
		ID3D11DeviceContext* const context,
		const std::wstring fileName)
	{
		HRESULT hr = S_OK;



		return S_OK;
	}

	//--------------------------------------------------------------------------------------
	void FbxMesh::DrawSubset(ID3D11DeviceContext* const context, const int id, const UINT testureSlot)
	{
		if (m_Material[id].NumFace == 0)
			return;

		// Set vertex buffer
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		context->IASetVertexBuffers(0, 1, m_Material[id].VertexBuffer.GetAddressOf(), &stride, &offset);
		// Set index buffer
		context->IASetIndexBuffer(m_Material[id].IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

		// Render a Cube
		context->DrawIndexed(m_Material[id].NumFace * 3, 0, 0);
	}
}