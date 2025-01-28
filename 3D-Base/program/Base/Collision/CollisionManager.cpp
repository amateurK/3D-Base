
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Փ˔�������Ȃ�Collider�R���|�[�l���g���Ǘ�����N���X
// �V���O���g���N���X
// 
// �����	: amateurK
// �쐬��	: 2025/01/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "CollisionManager.h"
#include "../Math/AK_Math.h"
#include "../Component/Collider.h"

namespace AK_Base {
	CollisionManager* CollisionManager::Instance = nullptr;

	//--------------------------------------------------------------------------------------
	CollisionManager::CollisionManager()
	{
		m_IsCollideCache.clear();
	}

	//--------------------------------------------------------------------------------------
	CollisionManager::~CollisionManager()
	{
		for (auto& collider : m_IsCollideCache)
		{
			collider.second.first.clear();
			collider.second.second.clear();
		}
		m_IsCollideCache.clear();
	}

	//--------------------------------------------------------------------------------------
	void CollisionManager::AddCollider(Collider* collider)
	{

		m_IsCollideCache[collider] = std::make_pair(std::unordered_set<Collider*>(), std::unordered_set<Collider*>());
	}

	//--------------------------------------------------------------------------------------
	void CollisionManager::RemoveCollider(Collider* collider)
	{

		auto itr = m_IsCollideCache.find(collider);
		if (itr != m_IsCollideCache.end()) {
			itr->second.first.clear();
			itr->second.second.clear();
			m_IsCollideCache.erase(itr);
		}
	}

	//--------------------------------------------------------------------------------------
	void CollisionManager::CollisionDetection()
	{
		// Collider�̍X�V
		for (auto& collider : m_IsCollideCache)
		{
			collider.first->CheckAbsolutePosUpdate();
			// �Փ˂��Ă���Collider�̃��X�g���N���A
			collider.second.first.clear();
			collider.second.second.clear();
		}
		// �Փ˔���
		// TODO : ���łɒ����ς݂̂��̂͂��Ȃ��Ă������悤�ɂ��Ă���������
		for (auto& collider : m_IsCollideCache)
		{
			for (auto& other : m_IsCollideCache)
			{
				// �������̓��m�̏ꍇ����
				if (collider.first == other.first)
				{
					continue;
				}
				// �Փ˔���
				if (collider.first->CheckCollision(other.first))
				{
					collider.first->OnCollision(other.first);

					// �Փ˂��Ă���Collider��o�^
					collider.second.first.insert(other.first);
				}
				else
				{
					// �Փ˂��Ă��Ȃ�Collider��o�^
					collider.second.second.insert(other.first);
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------
	std::unordered_set<Collider*>* CollisionManager::GetCollideSet(Collider* collider)
	{
		auto itr = m_IsCollideCache.find(collider);
		if (itr != m_IsCollideCache.end()) {
			return &itr->second.first;
		}
		return nullptr;
	}
}