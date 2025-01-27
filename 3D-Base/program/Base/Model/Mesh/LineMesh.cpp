
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 直線のメッシュデータ
// 
// 製作者	: amateurK
// 作成日	: 2025/01/27
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "LineMesh.h"

namespace Mesh {
	LineMesh::LineMesh()
	{

	}
	//--------------------------------------------------------------------------------------
	LineMesh::~LineMesh()
	{

	}

	//--------------------------------------------------------------------------------------
	HRESULT LineMesh::CreateMesh(ID3D11Device* const device,
		ID3D11DeviceContext* const context,
		const std::wstring fileName,
		ImportSettings* settings
	)
	{
		HRESULT hr = S_OK;

		// メッシュとテクスチャを入れる準備
		m_Mesh.clear();
		m_Texture.clear();

		// m_Materialにpushbackする用のデータ
		MeshData matData;

		// 頂点データ
		SimpleVertex vertices[] =
		{
			{ DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
			{ DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
		};
		matData.NumVertex = 2;

		// 頂点バッファを作成
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * matData.NumVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = vertices;
		hr = device->CreateBuffer(&bd, &InitData, matData.VertexBuffer.ReleaseAndGetAddressOf());
		if (FAILED(hr))
			return hr;

		// インデックスデータ
		size_t elementSize = sizeof(uint16_t);
		matData.DXGI_Format = DXGI_FORMAT_R16_UINT;
		matData.NumFace = 1;
		uint16_t indices[] =
		{
			0, 1
		};

		// インデックスバッファを作成
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = static_cast<UINT>(2 * elementSize);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = indices;

		hr = device->CreateBuffer(&bd, &InitData, matData.IndexBuffer.ReleaseAndGetAddressOf());
		if (FAILED(hr))
			return hr;

		// m_Materialに追加
		m_Mesh.push_back(std::move(matData));

		return hr;
	}

	//--------------------------------------------------------------------------------------
	void LineMesh::DrawSubset(ID3D11DeviceContext* const context, const int id, const UINT testureSlot)
	{

		// Set vertex buffer
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		context->IASetVertexBuffers(0, 1, m_Mesh[id].VertexBuffer.GetAddressOf(), &stride, &offset);
		// Set index buffer
		context->IASetIndexBuffer(m_Mesh[id].IndexBuffer.Get(), m_Mesh[id].DXGI_Format, 0);

		// 現在の設定を保存
		D3D11_PRIMITIVE_TOPOLOGY topology ;
		context->IAGetPrimitiveTopology(&topology);
		// 直線描画
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		context->Draw(2, 0);
		context->IASetPrimitiveTopology(topology);
	}
}