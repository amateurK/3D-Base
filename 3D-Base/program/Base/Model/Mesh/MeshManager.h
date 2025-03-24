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

	/// @brief ���b�V���f�[�^���Ǘ�����}�l�[�W���[�N���X
	class MeshManager
	{
	private:

		/// @brief �R���X�g���N�^
		MeshManager();
		/// @brief �f�X�g���N�^
		~MeshManager();

		static MeshManager* Instance;
	public:
		MeshManager(MeshManager&&) = delete;
		MeshManager& operator=(MeshManager&&) = delete;

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
		std::unordered_map<std::wstring, Mesh*> m_MeshList;

	public:
		/// @brief ���b�V�����쐬���Ď擾����
		/// @param fileName ���b�V���t�@�C���ւ̃p�X
		/// @param mesh �쐬�������b�V����Ԃ�
		/// @return ����Ɏ擾�ł�����
		HRESULT CreateMesh(const std::wstring& fileName, Mesh*& mesh);

		/// @brief �w�肵�����b�V����j������
		/// @param fileName �j�����������b�V���t�@�C���ւ̃p�X
		void DestroyMesh(const std::wstring& fileName);

		/// @brief ���b�V����S�Ĕj������
		void DestroyAllMesh();
	};
}