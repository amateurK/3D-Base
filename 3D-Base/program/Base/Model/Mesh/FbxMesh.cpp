
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// FBXファイルから読み込むメッシュデータ
// 
// 製作者	: amateurK
// 作成日	: 2024/08/05
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "FbxMesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../../Tools/WStringToString.h"


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
		// ImportSettingを初期状態にする
		// overrideしないでいい感じに実装できないかなぁ
		return CreateMesh(device, context, fileName, nullptr);
	}

	//--------------------------------------------------------------------------------------
	HRESULT FbxMesh::CreateMesh(ID3D11Device* const device,
		ID3D11DeviceContext* const context,
		const std::wstring fileName,
		ImportSettings* settings)
	{
		HRESULT hr = S_OK;

		// インポータを用意
		Assimp::Importer importer;
		auto path = Tools::WStringToString(fileName);

		int flag = 0;
		flag |= aiProcess_Triangulate;
		flag |= aiProcess_PreTransformVertices;
		flag |= aiProcess_CalcTangentSpace;
		flag |= aiProcess_GenSmoothNormals;
		flag |= aiProcess_GenUVCoords;
		flag |= aiProcess_RemoveRedundantMaterials;
		flag |= aiProcess_OptimizeMeshes;
		
		// ファイルの読み込み
		auto scene = importer.ReadFile(path, flag);
		if (scene == nullptr)
		{
			// 読み込み失敗
			throw std::exception("3Dデータのインポートに失敗");
			return E_FAIL;
		}


		// メッシュの作成
		m_Mesh = std::make_unique<MeshData>();

		// マテリアル数
		m_Mesh->NumMaterial = scene->mNumMeshes;

		// マテリアルのメモリ確保
		m_Material.clear();
		m_Material.resize(m_Mesh->NumMaterial);
		m_Material.shrink_to_fit(); // 今後追加することはたぶんないため

		// マテリアルごとにメッシュ情報を読み取り
		for (uint32_t i = 0; i < m_Mesh->NumMaterial; i++)
		{
			auto mesh = scene->mMeshes[i];
			m_Material[i].NumFace = mesh->mNumFaces;
			m_Material[i].NumVertex = mesh->mNumVertices;
			aiVector3D zeroVec3D(0.0f, 0.0f, 0.0f);


			// 頂点の読み込み
			SimpleVertex* vertices = new SimpleVertex[m_Material[i].NumVertex];
			for (uint32_t j = 0; j < m_Material[i].NumVertex; j++)
			{
				// aiVector3Dで渡されるので、ポインタでクッション
				auto pos = &(mesh->mVertices[j]);
				auto norm = &(mesh->mNormals[j]);
				auto uv = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][j]) : &zeroVec3D;
				if (settings != nullptr) {
					if (settings->InverseU)uv->x = 1 - uv->x;
					if (settings->InverseV)uv->y = 1 - uv->y;
				}

				vertices[j].Pos = DirectX::XMFLOAT3(pos->x, pos->y, pos->z);
				vertices[j].Normal = DirectX::XMFLOAT3(norm->x, norm->y, norm->z);
				vertices[j].Texcoord = DirectX::XMFLOAT2(uv->x, uv->y);
			}

			// 頂点バッファを作成
			D3D11_BUFFER_DESC bd = {};
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(SimpleVertex) * m_Material[i].NumVertex;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA InitData = {};
			InitData.pSysMem = vertices;
			hr = device->CreateBuffer(&bd, &InitData, m_Material[i].VertexBuffer.ReleaseAndGetAddressOf());
			delete[] vertices;
			if (FAILED(hr))
				return hr;

			// インデックスの読み込み
			WORD* indices = new WORD[m_Material[i].NumFace * 3];
			for (uint32_t j = 0; j < m_Material[i].NumFace; j++)
			{
				auto face = mesh->mFaces[j];
				
				indices[j * 3 + 0] = face.mIndices[0];
				indices[j * 3 + 1] = face.mIndices[1];
				indices[j * 3 + 2] = face.mIndices[2];
			}

			// インデックスバッファを作成
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(WORD) * m_Material[i].NumFace * 3;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;
			InitData.pSysMem = indices;
			hr = device->CreateBuffer(&bd, &InitData, m_Material[i].IndexBuffer.ReleaseAndGetAddressOf());
			delete[] indices;
			if (FAILED(hr))
				return hr;
		}

		scene = nullptr;

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