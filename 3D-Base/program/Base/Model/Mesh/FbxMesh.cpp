
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// FBX�t�@�C������ǂݍ��ރ��b�V���f�[�^
// 
// �����	: amateurK
// �쐬��	: 2024/08/05
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "FbxMesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// �Ή�����lib�t�@�C����ǂݍ���
#if defined( DEBUG ) || defined( _DEBUG )
// Debug�p
#pragma comment(lib, "../packages/Assimp_native_4.1_v142.4.1.0/build/native/lib/x64-Debug/assimp-vc142-mtd.lib")
#else
// Release�p
#pragma comment(lib, "../packages/Assimp_native_4.1_v142.4.1.0/build/native/lib/x64-Release/assimp-vc142-mt.lib")
#endif


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
		// ImportSetting��������Ԃɂ���
		// override���Ȃ��ł��������Ɏ����ł��Ȃ����Ȃ�
		return CreateMesh(device, context, fileName, nullptr);
	}

	//--------------------------------------------------------------------------------------
	HRESULT FbxMesh::CreateMesh(ID3D11Device* const device,
		ID3D11DeviceContext* const context,
		const std::wstring fileName,
		ImportSettings* settings)
	{
		HRESULT hr = S_OK;

		// �C���|�[�^��p��
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

		// �t�@�C���̓ǂݍ���
		auto scene = importer.ReadFile(path, flag);
		if (scene == nullptr)
		{
			// �ǂݍ��ݎ��s
			throw std::exception("3D�f�[�^�̃C���|�[�g�Ɏ��s");
			return E_FAIL;
		}


		// ���b�V���̍쐬
		m_Mesh = std::make_unique<MeshData>();

		// �}�e���A����
		m_Mesh->NumMaterial = scene->mNumMeshes;
		scene->mNumMaterials;
		// �}�e���A���̃������m��
		m_Material.clear();
		m_Material.resize(m_Mesh->NumMaterial);
		m_Material.shrink_to_fit(); // ����ǉ����邱�Ƃ͂��Ԃ�Ȃ�����

		// �}�e���A�����ƂɃ��b�V������ǂݎ��
		for (uint32_t i = 0; i < m_Mesh->NumMaterial; i++)
		{
			auto mesh = scene->mMeshes[i];
			m_Material[i].NumFace = mesh->mNumFaces;
			m_Material[i].NumVertex = mesh->mNumVertices;
			aiVector3D zeroVec3D(0.0f, 0.0f, 0.0f);


			// ���_�̓ǂݍ���
			SimpleVertex* vertices = new SimpleVertex[m_Material[i].NumVertex];
			for (uint32_t j = 0; j < m_Material[i].NumVertex; j++)
			{
				// aiVector3D�œn�����̂ŁA�|�C���^�ŃN�b�V����
				auto pos = &(mesh->mVertices[j]);
				auto norm = &(mesh->mNormals[j]);
				auto uv = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][j]) : &zeroVec3D;
				if (settings != nullptr) {
					if (settings->InverseU)uv->x = 1 - uv->x;
					if (settings->InverseV)uv->y = 1 - uv->y;
				}

				// TODO : �e�X�g�p�A�폜
				uv->y = 1 - uv->y;
				vertices[j].Pos = DirectX::XMFLOAT3(pos->x, pos->y, pos->z);
				vertices[j].Normal = DirectX::XMFLOAT3(norm->x, norm->y, norm->z);
				vertices[j].Texcoord = DirectX::XMFLOAT2(uv->x, uv->y);
			}

			// ���_�o�b�t�@���쐬
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

			// �C���f�b�N�X�̓ǂݍ���
			WORD* indices = new WORD[m_Material[i].NumFace * 3];
			for (uint32_t j = 0; j < m_Material[i].NumFace; j++)
			{
				auto face = mesh->mFaces[j];

				indices[j * 3 + 0] = face.mIndices[0];
				indices[j * 3 + 1] = face.mIndices[1];
				indices[j * 3 + 2] = face.mIndices[2];
			}

			// �C���f�b�N�X�o�b�t�@���쐬
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(WORD) * m_Material[i].NumFace * 3;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;
			InitData.pSysMem = indices;
			hr = device->CreateBuffer(&bd, &InitData, m_Material[i].IndexBuffer.ReleaseAndGetAddressOf());
			delete[] indices;
			if (FAILED(hr))
				return hr;

			// �e�N�X�`���̓ǂݍ���

			// NumMesh != NumMaterial �̂��Ƃ�����݂����H
			// i ���}�e���A�������z���Ȃ��悤�ɂ���
			aiMaterial* material;
			auto idx = i;
			if (scene->mNumMaterials <= i) {
				idx = scene->mNumMaterials - 1;
			}
			// ���̃}�e���A����Assimp���̃}�e���A��
			material = scene->mMaterials[idx];
			aiString path;

			// �p�X�̎擾
			if (material->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS)
			{
				auto file = std::string(path.C_Str());
				auto texPath = Tools::GetDirectoryPath(fileName) + L"/" + Tools::StringToWString(file);
				
				// TODO : �폜
				// psd�̏ꍇ��tga�ɕς���i���}���u�j

				if (true)
				{
					texPath = Tools::ReplaceExtension(texPath, L"tga");
				}

				hr = m_Material[i].Texture.LoadPicture(texPath);
				if (FAILED(hr))
					return hr;
			}
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

		// �摜���Z�b�g
		context->PSSetShaderResources(0, 1, m_Material[id].Texture.GetD3DSRView());

		// Render a Cube
		context->DrawIndexed(m_Material[id].NumFace * 3, 0, 0);
	}
}