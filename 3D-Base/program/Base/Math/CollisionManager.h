#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Փ˔�������Ȃ�Collider�R���|�[�l���g���Ǘ�����N���X
// �V���O���g���N���X
// 
// �����	: amateurK
// �쐬��	: 2025/01/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "../Component/Collider.h"


namespace AK_Base {

	__declspec(align(16))
		class CollisionManager {

		private:
			/// @brief �R���X�g���N�^
			CollisionManager();
			/// @brief �f�X�g���N�^
			~CollisionManager();

			static CollisionManager* Instance;
		public:
			CollisionManager(CollisionManager&&) = delete;
			CollisionManager& operator=(CollisionManager&&) = delete;

			CollisionManager(CollisionManager const&) = delete;
			CollisionManager& operator=(CollisionManager const&) = delete;

			/// @brief ���̃N���X�̃C���X�^���X���擾
			/// @return �C���X�^���X
			static CollisionManager* GetInstance() {
				return Instance;
			}
			/// @brief �C���X�^���X�𐶐�
			static void Create() {
				if (Instance == nullptr) {
					Instance = new CollisionManager;
				}
				else {
					throw std::exception("CollisionManager is a singleton");
				}
			}
			/// @brief �C���X�^���X�̉��
			static void Destroy() {
				delete Instance;
				Instance = nullptr;
			}

		private:
			/// @brief Collider�R���|�[�l���g�̃��X�g
			/// @details �L�[ : �o�^���郊�X�g�̖��O
			/// @details �l�@ : ���X�g
			std::unordered_map<std::string, std::vector<Collider*>> m_ColliderList;

			/// @brief �Փ˔�����s�����X�g
			/// @details ColliderList�̃C���f�b�N�X��pair�ɂ��Ēǉ�����
			std::vector<std::pair<std::string, std::string>> m_CheckList;

		public:

			/// @brief Collider�̃��X�g�ɒǉ�����
			/// @param listName �o�^���郊�X�g�̖��O
			/// @param ptr �o�^����Collider�̖��O
			void AddColliderList(const std::string& listName, Collider* ptr);

			/// @brief �����蔻����s���y�A��ǉ�
			/// @param listName1 ���X�g�̖��O
			/// @param listName2 ���X�g�̖��O�ilistName1�Ɠ����ł��悢�j
			void AddCkeckList(const std::string& listName1, const std::string& listName2);

			/// @brief �����蔻����s���y�A���폜
			/// @param listName1 ���X�g�̖��O
			/// @param listName2 ���X�g�̖��O
			void RemoveCheckList(const std::string& listName1, const std::string& listName2);

			/// @brief ���X�g����Collider���Փ˂��Ă��邩�𒲂ׂ�
			void CheckCollide(std::vector<Collider*>& list1, std::vector<Collider*> list2) const;
	};
}
