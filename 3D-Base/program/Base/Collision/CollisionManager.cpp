
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
		m_ColliderSet.clear();
	}

	//--------------------------------------------------------------------------------------
	CollisionManager::~CollisionManager()
	{
		m_ColliderSet.clear();
	}

	//--------------------------------------------------------------------------------------
	void CollisionManager::CollisionDetection()
	{
		// Collider�̍X�V
		for (auto& collider : m_ColliderSet)
		{
			collider->CheckAbsolutePosUpdate();
		}
		// �Փ˔���
		for (auto& collider : m_ColliderSet)
		{
			for (auto& other : m_ColliderSet)
			{
				if (collider == other)
				{
					continue;
				}
				if (collider->CheckCollision(other))
				{
					collider->OnCollision(other);
				}
			}
		}
	}
}