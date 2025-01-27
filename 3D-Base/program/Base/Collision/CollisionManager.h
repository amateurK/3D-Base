#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Փ˔�������Ȃ�Collider�R���|�[�l���g���Ǘ�����N���X
// �V���O���g���N���X
// 
// �����	: amateurK
// �쐬��	: 2025/01/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//#include "../Component/Collider.h"

//
// ���̂����������x���������Ȃ�Ǝv���̂ŁA���̂�����邱�Ƃ�����
// 1. Collision�𕡐��̃��X�g�ɕ�����
// �@"Enemy"�A"Player"�Ȃǂ̂悤�ȃ��X�g�ɕ�����
// �@"Enemy"���m�̏Փ˔���͍s��Ȃ��A"Enemy"��"EnemyBullet"�̏Փ˔���͍s��Ȃ��A�Ȃ�
// �@�K�v�ȃ��X�g�݂̂��Փ˔�����s�����Ƃŏ������x�����コ����
// 2. �Փ˔���̌��ʂ��L���b�V������
// 3. Octree����������
//�@�Փ˔�����s���I�u�W�F�N�g����ԕ������邱�ƂŁA�Փ˔���̑Ώۂ��i�荞��
// 4. ����l�p�ŃI�u�W�F�N�g���͂��A����ő�܂��ɏՓ˔�����s��
// �@3.������̂ŗv��Ȃ�����
//


namespace AK_Base {

	class Collider;
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

			/// @brief �Փ˔���̌��ʂ��L���b�V���iCollider�̃��X�g�����˂Ă���j
			/// @details 1�t���[�����ɓ���Collider���m�̏Փ˔���𕡐���s�����Ƃ�h��
			/// @details first : Collider, second : <first�ƏՓ˂��Ă���Collider�̏W��, first�ƏՓ˂��Ă��Ȃ�Collider�̏W��>
			std::unordered_map<Collider*, std::pair<std::unordered_set<Collider*>, std::unordered_set<Collider*>>> m_IsCollideCache;

		public:
			/// @brief Collider��ǉ�
			void AddCollider(Collider* collider);

			/// @brief Collider���폜
			void RemoveCollider(Collider* collider);

			/// @brief �Փ˔�����s��
			void CollisionDetection();

			/// @brief �Փ˂��Ă���Collider�̏W�����擾
			/// @param collider ���ׂ�Collider
			/// @return �W���̃|�C���^
			std::unordered_set<Collider*>* GetCollideSet(Collider* collider);
	};
}
