
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// VRM�t�@�C������ǂݍ��񂾃A�j���[�V�����t��3D���f�����Ǘ�����N���X
// 
// �����	: amateurK
// �쐬��	: 2025/02/08
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

		// �t�@�C���̃��[�h
		bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, Tools::WStringToString(fileName));
		if (!ret)
		{
			throw std::exception("�t�@�C���̃��[�h�Ɏ��s�B");
			return S_FALSE;
		}

		// ���b�V���ƃe�N�X�`�������鏀��
		m_Mesh.clear();
		m_Texture.clear();

		// �}�e���A�����ƂɃe�N�X�`����ǂݍ���
		for (const auto& material : model.materials) {

			// �}�e���A���̃v���p�e�B����e�N�X�`���̃C���f�b�N�X�����o��
			// ���̃C���f�b�N�X��VRM�t�@�C������textures�z��̃C���f�b�N�X�̂���
			if (material.values.find("baseColorTexture") != material.values.end()) {
				int textureIndex = material.values.at("baseColorTexture").TextureIndex();

				// �e�N�X�`���z�񂩂�e�N�X�`�����𔲂��o��
				if (textureIndex >= 0 && textureIndex < model.textures.size()) {
					const auto& texture = model.textures[textureIndex];
					// �摜�f�[�^���Q�Ƃ���C���f�b�N�X
					int imageIndex = texture.source;

					// �摜�f�[�^�����o��
					if (imageIndex >= 0 && imageIndex < model.images.size()) {
						const auto& image = model.images[imageIndex];

						AK_Base::PictureResource resource;
						// �摜�f�[�^�����[�h
						hr = resource.LoadPicture(image.image.data(),
							POINT(image.width, image.height), image.component);
						if (FAILED(hr))
						{
							throw std::exception("�e�N�X�`���̓ǂݍ��݂Ɏ��s�B");
						}

						// �e�N�X�`����ǉ�
						m_Texture.push_back(std::move(resource));
					}
				}
			}
		}

		// ���b�V������ǂݎ��
		for (const auto& mesh : model.meshes)
		{
			for (const auto& primitive : mesh.primitives) {

				// m_Material��pushback����p�̃f�[�^
				MeshData matData;

				std::vector<SkinningVertex> vertices;

				// ���_���W�̎擾
				const tinygltf::Accessor& posAccessor = model.accessors[primitive.attributes.find("POSITION")->second];
				const tinygltf::BufferView& posBufferView = model.bufferViews[posAccessor.bufferView];
				const tinygltf::Buffer& posBuffer = model.buffers[posBufferView.buffer];
				const float* positions = reinterpret_cast<const float*>(&posBuffer.data[posBufferView.byteOffset + posAccessor.byteOffset]);
				// �@�������擾
				const tinygltf::Accessor& normAccessor = model.accessors[primitive.attributes.find("NORMAL")->second];
				const tinygltf::BufferView& normBufferView = model.bufferViews[normAccessor.bufferView];
				const tinygltf::Buffer& normBuffer = model.buffers[normBufferView.buffer];
				const float* normals = reinterpret_cast<const float*>(&normBuffer.data[normBufferView.byteOffset + normAccessor.byteOffset]);
				// UV���W�̎擾
				const tinygltf::Accessor& texAccessor = model.accessors[primitive.attributes.find("TEXCOORD_0")->second];
				const tinygltf::BufferView& texBufferView = model.bufferViews[texAccessor.bufferView];
				const tinygltf::Buffer& texBuffer = model.buffers[texBufferView.buffer];
				const float* texcoords = reinterpret_cast<const float*>(&texBuffer.data[texBufferView.byteOffset + texAccessor.byteOffset]);

				// �e���_�̉e�����󂯂�{�[���̃C���f�b�N�X���擾
				const tinygltf::Accessor& jointAccessor = model.accessors[primitive.attributes.find("JOINTS_0")->second];
				const tinygltf::BufferView& jointBufferView = model.bufferViews[jointAccessor.bufferView];
				const tinygltf::Buffer& jointBuffer = model.buffers[jointBufferView.buffer];
				const uint16_t* joints = reinterpret_cast<const uint16_t*>(&jointBuffer.data[jointBufferView.byteOffset + jointAccessor.byteOffset]);
				// �e���_�̉e�����󂯂�{�[���̏d�݂��擾
				const tinygltf::Accessor& weightAccessor = model.accessors[primitive.attributes.find("WEIGHTS_0")->second];
				const tinygltf::BufferView& weightBufferView = model.bufferViews[weightAccessor.bufferView];
				const tinygltf::Buffer& weightBuffer = model.buffers[weightBufferView.buffer];
				const float* weights = reinterpret_cast<const float*>(&weightBuffer.data[weightBufferView.byteOffset + weightAccessor.byteOffset]);

				// �擾�����������ɒ��_�o�b�t�@�p�z��ɓ����
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

				// ���_�o�b�t�@���쐬
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


				// �C���f�b�N�X�f�[�^�̎擾
				const tinygltf::Accessor& indexAccessor = model.accessors[primitive.indices];
				const tinygltf::BufferView& indexBufferView = model.bufferViews[indexAccessor.bufferView];
				const auto bufferData = &model.buffers[indexBufferView.buffer].data[indexBufferView.byteOffset + indexAccessor.byteOffset];

				// 1�f�[�^������̃T�C�Y���Ƃɏ���
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

				// �C���f�b�N�X�o�b�t�@���쐬
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = static_cast<UINT>(indexAccessor.count * elementSize);
				bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
				bd.CPUAccessFlags = 0;
				InitData.pSysMem = bufferData;

				hr = device->CreateBuffer(&bd, &InitData, matData.IndexBuffer.ReleaseAndGetAddressOf());
				if (FAILED(hr))
					return hr;

				// �g�p����e�N�X�`���̃��\�[�X�r���[��ݒ�
				auto matIndex = primitive.material;
				if (matIndex >= 0 && matIndex < m_Texture.size()) {
					matData.SRView = m_Texture[matIndex].GetD3DSRView();
				}
				else {
					matData.SRView = nullptr;
				}

				// m_Material�ɒǉ�
				m_Mesh.push_back(std::move(matData));


				// �A�j���[�V�����f�[�^�̓ǂݍ���

				// pushback�p�̃f�[�^
				SkinningData skinningData;

				// �T�C�Y�̊m��
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

		// VRM�̃{�[������ǂݍ���
		// VRM�͊g���@�\�����Ƀ{�[����񂪊i�[����Ă���
		// JSON����͂��ă{�[�������擾���Ȃ���΂����Ȃ�
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

					// �e�{�[�����擾��boneIndexMap�Ɋi�[
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
						// useDefaultValues ��false�̎��͍l�����Ă��Ȃ�

						// �{�[���̃C���f�b�N�X�Ɩ��O���i�[
						boneIndexMap[nodeID->second.Get<int>()] = boneName->second.Get<std::string>();
					}
				}
			}
		}

		// �{�[���f�[�^�̓ǂݍ���
		// skin����������ꍇ�A1�߂̌�ɒǉ����Ă��������Ȃ̂ŁA1�߂̕��ȊO�͂��炵�ĎQ�Ƃ���K�v������
		// TODO : �Ō��break���Ă��邽�߁A2�܈ȍ~�g�p����ꍇ�͕K�v�ɉ����đΉ��iVRMA�̍\������j
		//int offset = 0;
		for (const auto& skin : model.skins)
		{
			// �t�o�C���h�s��̎擾
			const tinygltf::Accessor& skinAccessor = model.accessors[skin.inverseBindMatrices];
			const tinygltf::BufferView& skinBufferView = model.bufferViews[skinAccessor.bufferView];
			const tinygltf::Buffer& skinBuffer = model.buffers[skinBufferView.buffer];
			const float* skins = reinterpret_cast<const float*>(&skinBuffer.data[skinBufferView.byteOffset + skinAccessor.byteOffset]);

			// �{�[���f�[�^�̍쐬�E���W�̓ǂݎ��
			for (int i = 0; i < skinAccessor.count; ++i)
			{
				BoneData boneData;

				DirectX::XMMATRIX matrix;
				matrix.r[0] = DirectX::XMVectorSet(skins[i * 16], skins[i * 16 + 1], skins[i * 16 + 2], skins[i * 16 + 3]);
				matrix.r[1] = DirectX::XMVectorSet(skins[i * 16 + 4], skins[i * 16 + 5], skins[i * 16 + 6], skins[i * 16 + 7]);
				matrix.r[2] = DirectX::XMVectorSet(skins[i * 16 + 8], skins[i * 16 + 9], skins[i * 16 + 10], skins[i * 16 + 11]);
				matrix.r[3] = DirectX::XMVectorSet(skins[i * 16 + 12], skins[i * 16 + 13], skins[i * 16 + 14], skins[i * 16 + 15]);
				
				boneData.InverseBindMatrix = matrix;
				boneData.FirstChild = nullptr;	// �|�C���^���������g = ���ݒ�Ȃ̂ŃG���[
				boneData.NextSibling = nullptr;		// �e�q�ƈႢ�A���[�g�m�[�h�͐ݒ肳��Ȃ��\��������̂�nullptr

				boneData.ID = i;
				const auto& nameItr = boneIndexMap.find(i);
				if (nameItr != boneIndexMap.end())
				{
					// VRM�A�j���[�V�����p�̃{�[����
					boneData.Name = nameItr->second;
				}
				else
				{
					// �{�[�������Ȃ��ꍇ��ID�𖼑O�Ƃ���
					boneData.Name = "Bone" + std::to_string(i);
				}
				m_BoneData.push_back(std::move(boneData));
				m_BoneDataHashmap[model.nodes[skin.joints[i]].name] = &m_BoneData.back();	// move���Ă��邪�A�O�̂���vector�ɂ���Ă���Q�Ƃ���
			}
			// �m�[�h����擾����f�[�^�̐ݒ�
			for (size_t i = 0; i < skinAccessor.count; ++i)
			{
				const auto& node = model.nodes[skin.joints[i]];
				// �e�q�֌W�̎擾
				// �e�q�͎����̃��[�v�Őݒ肳���
				// �Z��͐e�̃��[�v�Őݒ肳���
				if (node.children.size() == 0)
				{
					m_BoneData[i].FirstChild = nullptr;
				}
				else
				{
					m_BoneData[i].FirstChild = &m_BoneData[node.children[0]];
					// �Z���ݒ�
					for (size_t j = 1; j < node.children.size(); ++j)
					{
						m_BoneData[node.children[j - 1]].NextSibling = &m_BoneData[node.children[j]];
					}
					m_BoneData[node.children[node.children.size() - 1]].NextSibling = nullptr;
				}

				// ���[�J�����W�̎擾
				if (node.translation.size() == 0) {
					// �f�[�^���Ȃ��ꍇ�͏������
					m_BoneData[i].LocalMatrix = DirectX::XMMatrixIdentity();
				}
				else
				{
					// �f�[�^������ꍇ�͍��W��ݒ�
					const auto& trans = node.translation;
					m_BoneData[i].LocalMatrix = DirectX::XMMatrixTranslation(trans[0], trans[1], trans[2]);
				}
			}
			// 2���߈ȍ~��skin�͖���
			break;
			// ���݂͖��g�p
			//// skin����������ꍇ�̃I�t�Z�b�g
			//offset += static_cast<int>(skinAccessor.count);
		}

		// children�̃����������邩��_������
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

		// �摜���Z�b�g
		if (m_Mesh[id].SRView != nullptr) {
			context->PSSetShaderResources(textureSlot, 1, m_Mesh[id].SRView);
		}

		// Render a Cube
		context->DrawIndexed(m_Mesh[id].NumFace * 3, 0, 0);
	}
}