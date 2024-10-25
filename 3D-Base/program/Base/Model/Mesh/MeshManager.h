#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���b�V���f�[�^���Ǘ�����}�l�[�W���[�N���X
// �V���O���g���N���X
// 
// �����	: amateurK
// �쐬��	: 2024/07/29
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Mesh.h"

namespace Mesh {

	enum class MeshType {
		BasicMesh,
		FbxMesh,
	};

	/// @brief ���b�V���f�[�^���Ǘ�����}�l�[�W���[�N���X
	class MeshManager
	{
	private:
		/// @brief ���b�V���N���X�Ɩ��O�̃Z�b�g
		struct MeshData {
			std::wstring Name;
			Mesh* Mesh;
		};

		/// @brief �R���X�g���N�^
		MeshManager();
		/// @brief �f�X�g���N�^
		~MeshManager();

		static MeshManager* Instance;
	public:
		MeshManager(MeshManager&& moveFrom) = delete;
		MeshManager& operator=(MeshManager&& moveFrom) = delete;

		MeshManager(MeshManager const&) = delete;
		MeshManager& operator=(MeshManager const&) = delete;

		/// @brief ���̃N���X�̃C���X�^���X���擾
		/// @return �C���X�^���X
		static MeshManager* GetInstance() {
			return Instance;
		}
		/// @brief �C���X�^���X�𐶐�
		static void Create() {
			if (Instance == nullptr) {
				Instance = new MeshManager;
			}
			else {
				throw std::exception("MeshManager is a singleton");
			}
		}
		/// @brief �C���X�^���X�̉��
		static void Destroy() {
			delete Instance;
			Instance = nullptr;
		}

	private:
		/// @brief ���b�V���̃��X�g
		std::list<MeshData> m_MeshList;

	public:
		/// @brief ���b�V�����쐬���Ď擾����
		/// @param fileName ���b�V���t�@�C���ւ̃p�X
		/// @param mesh �쐬�������b�V����Ԃ�
		/// @return ����Ɏ擾�ł�����
		HRESULT CreateMesh(std::wstring& fileName, MeshType meshType, Mesh*& mesh);

		/// @brief �w�肵�����b�V����j������
		/// @param fileName �j�����������b�V���t�@�C���ւ̃p�X
		void DestroyMesh(std::wstring& fileName);

		/// @brief ���b�V����S�Ĕj������
		void DestroyAllMesh();
	};
}