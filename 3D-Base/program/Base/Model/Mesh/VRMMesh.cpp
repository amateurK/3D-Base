
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// VRMファイルから読み込むメッシュデータ
// 
// VRMは主にVR等に使われる3Dデータの拡張子
// VRoidStudioなどで出力されるのもこの型
// 
// tiny_gltf.hを使用
// https://github.com/syoyo/tinygltf/tree/release
// 
// 製作者	: amateurK
// 作成日	: 2024/11/07
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "VRMMesh.h"
#include "../../Reader/tiny_gltf.h"


namespace Mesh {

	VRMMesh::VRMMesh()
	{

	}

	//--------------------------------------------------------------------------------------
	VRMMesh::~VRMMesh()
	{

	}

	//--------------------------------------------------------------------------------------
	void VRMMesh::DestroyMesh()
	{

	}

	//--------------------------------------------------------------------------------------
	HRESULT VRMMesh::CreateMesh(ID3D11Device* const device,
		ID3D11DeviceContext* const context,
		const std::wstring fileName,
		ImportSettings* settings)
	{
		HRESULT hr = S_OK;

		tinygltf::Model model;
		tinygltf::TinyGLTF loader;

		std::string err, warn;

		// ファイルのロード
		bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, Tools::WStringToString(fileName));
		if (!ret)
		{
			throw std::exception("ファイルのロードに失敗。");
			return S_FALSE;
		}

		// メッシュとテクスチャを入れる準備
		m_Mesh.clear();
		m_Texture.clear();

		// マテリアルごとにテクスチャを読み込み
		for (const auto& material : model.materials) {

			// マテリアルのプロパティからテクスチャのインデックスを取り出す
			// このインデックスはVRMファイル内のtextures配列のインデックスのこと
			if (material.values.find("baseColorTexture") != material.values.end()) {
				int textureIndex = material.values.at("baseColorTexture").TextureIndex();
				
				// テクスチャ配列からテクスチャ情報を抜き出す
				if (textureIndex >= 0 && textureIndex < model.textures.size()) {
					const auto& texture = model.textures[textureIndex];
					// 画像データを参照するインデックス
					int imageIndex = texture.source;

					// 画像データを取り出す
					if (imageIndex >= 0 && imageIndex < model.images.size()) {
						const auto& image = model.images[imageIndex];

						AK_Base::PictureResource resource;
						// 画像データをロード
						hr = resource.LoadPicture(image.image.data(),
							Point<int>(image.width, image.height), image.component);
						if (FAILED(hr)) 
						{
							throw std::exception("テクスチャの読み込みに失敗。");
						}

						// テクスチャを追加
						m_Texture.push_back(std::move(resource));
					}
				}
			}
		}


		// メッシュ情報を読み取り
		for (const auto& mesh : model.meshes)
		{
			for (const auto& primitive : mesh.primitives) {

				// m_Materialにpushbackする用のデータ
				MeshData matData;

				std::vector<SimpleVertex> vertices;
				std::vector<WORD> indices;

				// 頂点座標の取得
				const tinygltf::Accessor& posAccessor = model.accessors[primitive.attributes.find("POSITION")->second];
				const tinygltf::BufferView& posBufferView = model.bufferViews[posAccessor.bufferView];
				const tinygltf::Buffer& posBuffer = model.buffers[posBufferView.buffer];
				const float* positions = reinterpret_cast<const float*>(&posBuffer.data[posBufferView.byteOffset + posAccessor.byteOffset]);
				// 法線情報を取得
				const tinygltf::Accessor& normAccessor = model.accessors[primitive.attributes.find("NORMAL")->second];
				const tinygltf::BufferView& normBufferView = model.bufferViews[normAccessor.bufferView];
				const tinygltf::Buffer& normBuffer = model.buffers[normBufferView.buffer];
				const float* normals = reinterpret_cast<const float*>(&normBuffer.data[normBufferView.byteOffset + normAccessor.byteOffset]);
				// UV座標の取得
				const tinygltf::Accessor& texAccessor = model.accessors[primitive.attributes.find("TEXCOORD_0")->second];
				const tinygltf::BufferView& texBufferView = model.bufferViews[texAccessor.bufferView];
				const tinygltf::Buffer& texBuffer = model.buffers[texBufferView.buffer];
				const float* texcoords = reinterpret_cast<const float*>(&texBuffer.data[texBufferView.byteOffset + texAccessor.byteOffset]);

				// 取得した情報を元に頂点バッファ用配列に入れる
				for (size_t i = 0; i < posAccessor.count; ++i) {
					SimpleVertex vertex;
					vertex.Pos = DirectX::XMFLOAT3(positions[i * 3], positions[i * 3 + 1], positions[i * 3 + 2]);
					vertex.Normal = DirectX::XMFLOAT3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]);
					vertex.Texcoord = DirectX::XMFLOAT2(texcoords[i * 2], texcoords[i * 2 + 1]);
					vertices.push_back(std::move(vertex));
				}
				matData.NumVertex = static_cast<uint32_t>(vertices.size());

				// 頂点バッファを作成
				D3D11_BUFFER_DESC bd = {};
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(SimpleVertex) * matData.NumVertex;
				bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				bd.CPUAccessFlags = 0;
				D3D11_SUBRESOURCE_DATA InitData = {};
				InitData.pSysMem = vertices.data();
				hr = device->CreateBuffer(&bd, &InitData, matData.VertexBuffer.ReleaseAndGetAddressOf());
				vertices.clear();
				if (FAILED(hr))
					return hr;


				// インデックスデータの取得
				const tinygltf::Accessor& indexAccessor = model.accessors[primitive.indices];
				const tinygltf::BufferView& indexBufferView = model.bufferViews[indexAccessor.bufferView];
				const uint32_t* indexData = reinterpret_cast<const uint32_t*>(&model.buffers[indexBufferView.buffer].data[indexBufferView.byteOffset + indexAccessor.byteOffset]);

				// インデックスバッファ用配列に入れる
				for (size_t i = 0; i < indexAccessor.count; ++i) {
					indices.push_back(std::move(static_cast<WORD>(indexData[i])));
				}
				matData.NumFace = static_cast<uint32_t>(indices.size()) / 3;

				// インデックスバッファを作成
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(WORD) * static_cast<UINT>(indices.size());
				bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
				bd.CPUAccessFlags = 0;
				InitData.pSysMem = indices.data();
				hr = device->CreateBuffer(&bd, &InitData, matData.IndexBuffer.ReleaseAndGetAddressOf());
				indices.clear();
				if (FAILED(hr))
					return hr;

				// 使用するテクスチャのリソースビューを設定
				auto matIndex = primitive.material;
				if (matIndex >= 0 && matIndex < m_Texture.size()) {
					matData.SRView = m_Texture[matIndex].GetD3DSRView();
				}
				else {
					matData.SRView = nullptr;
				}

				// m_Materialに追加
				m_Mesh.push_back(std::move(matData));
			}
		}

		return S_OK;
	}

	//--------------------------------------------------------------------------------------
	void VRMMesh::DrawSubset(ID3D11DeviceContext* const context, const int id, const UINT textureSlot)
	{
		if (m_Mesh[id].NumFace == 0)
			return;

		// Set vertex buffer
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		context->IASetVertexBuffers(0, 1, m_Mesh[id].VertexBuffer.GetAddressOf(), &stride, &offset);
		// Set index buffer
		context->IASetIndexBuffer(m_Mesh[id].IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

		// 画像をセット
		if (m_Mesh[id].SRView != nullptr) {
			context->PSSetShaderResources(textureSlot, 1, m_Mesh[id].SRView);
		}

		// Render a Cube
		context->DrawIndexed(m_Mesh[id].NumFace * 3, 0, 0);
	}
}