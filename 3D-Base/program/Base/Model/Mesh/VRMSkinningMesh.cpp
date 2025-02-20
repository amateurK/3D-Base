
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// VRMファイルから読み込んだアニメーション付き3Dモデルを管理するクラス
// 
// 製作者	: amateurK
// 作成日	: 2025/02/08
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "VRMSkinningMesh.h"
#include "../../Reader/tiny_gltf.h"

namespace Mesh {

	VRMSkinningMesh::VRMSkinningMesh()
	{

	}

	//--------------------------------------------------------------------------------------
	VRMSkinningMesh::~VRMSkinningMesh()
	{

	}

	//--------------------------------------------------------------------------------------
	HRESULT VRMSkinningMesh::CreateMesh(ID3D11Device* const device,
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
							POINT(image.width, image.height), image.component);
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

				std::vector<SkinningVertex> vertices;

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

				// 各頂点の影響を受けるボーンのインデックスを取得
				const tinygltf::Accessor& jointAccessor = model.accessors[primitive.attributes.find("JOINTS_0")->second];
				const tinygltf::BufferView& jointBufferView = model.bufferViews[jointAccessor.bufferView];
				const tinygltf::Buffer& jointBuffer = model.buffers[jointBufferView.buffer];
				const uint16_t* joints = reinterpret_cast<const uint16_t*>(&jointBuffer.data[jointBufferView.byteOffset + jointAccessor.byteOffset]);
				// 各頂点の影響を受けるボーンの重みを取得
				const tinygltf::Accessor& weightAccessor = model.accessors[primitive.attributes.find("WEIGHTS_0")->second];
				const tinygltf::BufferView& weightBufferView = model.bufferViews[weightAccessor.bufferView];
				const tinygltf::Buffer& weightBuffer = model.buffers[weightBufferView.buffer];
				const float* weights = reinterpret_cast<const float*>(&weightBuffer.data[weightBufferView.byteOffset + weightAccessor.byteOffset]);

				// 取得した情報を元に頂点バッファ用配列に入れる
				for (size_t i = 0; i < posAccessor.count; ++i) {
					SkinningVertex vertex;
					vertex.Pos = DirectX::XMFLOAT3(positions[i * 3], positions[i * 3 + 1], positions[i * 3 + 2]);
					vertex.Normal = DirectX::XMFLOAT3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]);
					vertex.Texcoord = DirectX::XMFLOAT2(texcoords[i * 2], texcoords[i * 2 + 1]);
					for (int j = 0; j < 4; j++) {
						vertex.BoneIndices[j] = static_cast<uint8_t>(joints[i * 4 + j]);
					}
					vertex.BoneWeight = DirectX::XMFLOAT4(weights[i * 4], weights[i * 4 + 1], weights[i * 4 + 2], weights[i * 4 + 3]);
					vertices.push_back(std::move(vertex));
				}
				matData.NumVertex = static_cast<uint32_t>(vertices.size());

				// 頂点バッファを作成
				D3D11_BUFFER_DESC bd = {};
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(SkinningVertex) * matData.NumVertex;
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
				const auto bufferData = &model.buffers[indexBufferView.buffer].data[indexBufferView.byteOffset + indexAccessor.byteOffset];

				// 1データあたりのサイズごとに処理
				size_t elementSize = 0;
				if (indexAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
					matData.DXGI_Format = DXGI_FORMAT_R16_UINT;
					elementSize = sizeof(uint16_t);
				}
				else if (indexAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
					matData.DXGI_Format = DXGI_FORMAT_R32_UINT;
					elementSize = sizeof(uint32_t);
				}
				else {
					return E_FAIL;
				}

				matData.NumFace = static_cast<uint32_t>(indexAccessor.count) / 3;

				// インデックスバッファを作成
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = static_cast<UINT>(indexAccessor.count * elementSize);
				bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
				bd.CPUAccessFlags = 0;
				InitData.pSysMem = bufferData;

				hr = device->CreateBuffer(&bd, &InitData, matData.IndexBuffer.ReleaseAndGetAddressOf());
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


				// アニメーションデータの読み込み

				// pushback用のデータ
				SkinningData skinningData;

				// サイズの確保
				if (jointAccessor.count != weightAccessor.count) {
					return E_FAIL;
				}
				skinningData.BoneIndices.resize(jointAccessor.count);
				skinningData.BoneWeights.resize(weightAccessor.count);
				for (size_t i = 0; i < jointAccessor.count; i++)
				{
					skinningData.BoneIndices[i] = {
						static_cast<uint8_t>(joints[i * 4]),
						static_cast<uint8_t>(joints[i * 4 + 1]),
						static_cast<uint8_t>(joints[i * 4 + 2]),
						static_cast<uint8_t>(joints[i * 4 + 3])
					};
					skinningData.BoneWeights[i] = {
						weights[i * 4],
						weights[i * 4 + 1],
						weights[i * 4 + 2],
						weights[i * 4 + 3]
					};
				}

				m_SkinningData.push_back(std::move(skinningData));

			}
		}

		// VRMのボーン情報を読み込み
		// VRMは拡張機能部分にボーン情報が格納されている
		// JSONを解析してボーン情報を取得しなければいけない
		std::unordered_map<int, std::string> boneIndexMap;
		const auto& vrmItr = model.extensions.find("VRM");
		if (vrmItr != model.extensions.end())
		{
			const auto& vrm = vrmItr->second.Get<tinygltf::Value::Object>();
			const auto& humanoidItr = vrm.find("humanoid");
			if (humanoidItr != vrm.end())
			{
				const auto& humanoid = humanoidItr->second.Get<tinygltf::Value::Object>();
				const auto& humanBonesItr = humanoid.find("humanBones");
				if (humanBonesItr != humanoid.end())
				{
					auto& humanBones = humanBonesItr->second.Get<tinygltf::Value::Array>();

					// 各ボーンを取得しboneIndexMapに格納
					for (const auto& bone : humanBones)
					{
						const auto& nodeID = bone.Get<tinygltf::Value::Object>().find("node");
						if (nodeID == bone.Get<tinygltf::Value::Object>().end())
						{
							continue;
						}
						const auto& boneName = bone.Get<tinygltf::Value::Object>().find("bone");
						if (nodeID == bone.Get<tinygltf::Value::Object>().end())
						{
							continue;
						}
						// useDefaultValues がfalseの時は考慮していない

						// ボーンのインデックスと名前を格納
						boneIndexMap[nodeID->second.Get<int>()] = boneName->second.Get<std::string>();
					}
				}
			}
		}

		// ボーンデータの読み込み
		// skinが複数個ある場合、1つめの後に追加していく方式なので、1つめの物以外はずらして参照する必要がある
		// TODO : 最後にbreakしているため、2爪以降使用する場合は必要に応じて対応（VRMAの構造次第）
		//int offset = 0;
		for (const auto& skin : model.skins)
		{
			// 逆バインド行列の取得
			const tinygltf::Accessor& skinAccessor = model.accessors[skin.inverseBindMatrices];
			const tinygltf::BufferView& skinBufferView = model.bufferViews[skinAccessor.bufferView];
			const tinygltf::Buffer& skinBuffer = model.buffers[skinBufferView.buffer];
			const float* skins = reinterpret_cast<const float*>(&skinBuffer.data[skinBufferView.byteOffset + skinAccessor.byteOffset]);

			// ボーンデータの作成・座標の読み取り
			for (int i = 0; i < skinAccessor.count; ++i)
			{
				BoneData boneData;

				DirectX::XMMATRIX matrix;
				matrix.r[0] = DirectX::XMVectorSet(skins[i * 16], skins[i * 16 + 1], skins[i * 16 + 2], skins[i * 16 + 3]);
				matrix.r[1] = DirectX::XMVectorSet(skins[i * 16 + 4], skins[i * 16 + 5], skins[i * 16 + 6], skins[i * 16 + 7]);
				matrix.r[2] = DirectX::XMVectorSet(skins[i * 16 + 8], skins[i * 16 + 9], skins[i * 16 + 10], skins[i * 16 + 11]);
				matrix.r[3] = DirectX::XMVectorSet(skins[i * 16 + 12], skins[i * 16 + 13], skins[i * 16 + 14], skins[i * 16 + 15]);
				
				boneData.InverseBindMatrix = matrix;
				boneData.FirstChild = nullptr;	// ポインタが自分自身 = 未設定なのでエラー
				boneData.NextSibling = nullptr;		// 親子と違い、ルートノードは設定されない可能性があるのでnullptr

				boneData.ID = i;
				const auto& nameItr = boneIndexMap.find(i);
				if (nameItr != boneIndexMap.end())
				{
					// VRMアニメーション用のボーン名
					boneData.Name = nameItr->second;
				}
				else
				{
					// ボーン名がない場合はIDを名前とする
					boneData.Name = "Bone" + std::to_string(i);
				}
				m_BoneData.push_back(std::move(boneData));
				m_BoneDataHashmap[model.nodes[skin.joints[i]].name] = &m_BoneData.back();	// moveしているが、念のためvectorにいれてから参照する
			}
			// ノードから取得するデータの設定
			for (size_t i = 0; i < skinAccessor.count; ++i)
			{
				const auto& node = model.nodes[skin.joints[i]];
				// 親子関係の取得
				// 親子は自分のループで設定される
				// 兄弟は親のループで設定される
				if (node.children.size() == 0)
				{
					m_BoneData[i].FirstChild = nullptr;
				}
				else
				{
					m_BoneData[i].FirstChild = &m_BoneData[node.children[0]];
					// 兄弟を設定
					for (size_t j = 1; j < node.children.size(); ++j)
					{
						m_BoneData[node.children[j - 1]].NextSibling = &m_BoneData[node.children[j]];
					}
					m_BoneData[node.children[node.children.size() - 1]].NextSibling = nullptr;
				}

				// ローカル座標の取得
				if (node.translation.size() == 0) {
					// データがない場合は初期状態
					m_BoneData[i].LocalMatrix = DirectX::XMMatrixIdentity();
				}
				else
				{
					// データがある場合は座標を設定
					const auto& trans = node.translation;
					m_BoneData[i].LocalMatrix = DirectX::XMMatrixTranslation(trans[0], trans[1], trans[2]);
				}
			}
			// 2こめ以降のskinは無視
			break;
			// 現在は未使用
			//// skinが複数ある場合のオフセット
			//offset += static_cast<int>(skinAccessor.count);
		}

		// childrenのメモリが壊れるからダメそう
		//m_BoneData.shrink_to_fit();
		return S_OK;
	}

	//--------------------------------------------------------------------------------------
	void VRMSkinningMesh::DrawSubset(ID3D11DeviceContext* const context, const int id, const UINT textureSlot)
	{
		if (m_Mesh[id].NumFace == 0)
			return;

		// Set vertex buffer
		UINT stride = sizeof(SkinningVertex);
		UINT offset = 0;
		context->IASetVertexBuffers(0, 1, m_Mesh[id].VertexBuffer.GetAddressOf(), &stride, &offset);
		// Set index buffer
		context->IASetIndexBuffer(m_Mesh[id].IndexBuffer.Get(), m_Mesh[id].DXGI_Format, 0);

		// 画像をセット
		if (m_Mesh[id].SRView != nullptr) {
			context->PSSetShaderResources(textureSlot, 1, m_Mesh[id].SRView);
		}

		// Render a Cube
		context->DrawIndexed(m_Mesh[id].NumFace * 3, 0, 0);
	}
}