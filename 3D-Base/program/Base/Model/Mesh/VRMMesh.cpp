
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// VRM�t�@�C������ǂݍ��ރ��b�V���f�[�^
// 
// VRM�͎��VR���Ɏg����3D�f�[�^�̊g���q
// VRoidStudio�Ȃǂŏo�͂����̂����̌^
// 
// tiny_gltf.h���g�p
// https://github.com/syoyo/tinygltf/tree/release
// 
// �����	: amateurK
// �쐬��	: 2024/11/07
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
							Point<int>(image.width, image.height), image.component);
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

				std::vector<SimpleVertex> vertices;
				std::vector<WORD> indices;

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

				// �擾�����������ɒ��_�o�b�t�@�p�z��ɓ����
				for (size_t i = 0; i < posAccessor.count; ++i) {
					SimpleVertex vertex;
					vertex.Pos = DirectX::XMFLOAT3(positions[i * 3], positions[i * 3 + 1], positions[i * 3 + 2]);
					vertex.Normal = DirectX::XMFLOAT3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]);
					vertex.Texcoord = DirectX::XMFLOAT2(texcoords[i * 2], texcoords[i * 2 + 1]);
					vertices.push_back(std::move(vertex));
				}
				matData.NumVertex = static_cast<uint32_t>(vertices.size());

				// ���_�o�b�t�@���쐬
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


				// �C���f�b�N�X�f�[�^�̎擾
				const tinygltf::Accessor& indexAccessor = model.accessors[primitive.indices];
				const tinygltf::BufferView& indexBufferView = model.bufferViews[indexAccessor.bufferView];
				const uint32_t* indexData = reinterpret_cast<const uint32_t*>(&model.buffers[indexBufferView.buffer].data[indexBufferView.byteOffset + indexAccessor.byteOffset]);

				// �C���f�b�N�X�o�b�t�@�p�z��ɓ����
				for (size_t i = 0; i < indexAccessor.count; ++i) {
					indices.push_back(std::move(static_cast<WORD>(indexData[i])));
				}
				matData.NumFace = static_cast<uint32_t>(indices.size()) / 3;

				// �C���f�b�N�X�o�b�t�@���쐬
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(WORD) * static_cast<UINT>(indices.size());
				bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
				bd.CPUAccessFlags = 0;
				InitData.pSysMem = indices.data();
				hr = device->CreateBuffer(&bd, &InitData, matData.IndexBuffer.ReleaseAndGetAddressOf());
				indices.clear();
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

		// �摜���Z�b�g
		if (m_Mesh[id].SRView != nullptr) {
			context->PSSetShaderResources(textureSlot, 1, m_Mesh[id].SRView);
		}

		// Render a Cube
		context->DrawIndexed(m_Mesh[id].NumFace * 3, 0, 0);
	}
}