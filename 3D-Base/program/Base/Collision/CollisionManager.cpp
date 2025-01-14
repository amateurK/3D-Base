
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 衝突判定を奥なうColliderコンポーネントを管理するクラス
// シングルトンクラス
// 
// 製作者	: amateurK
// 作成日	: 2025/01/01
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
		// Colliderの更新
		for (auto& collider : m_ColliderSet)
		{
			collider->CheckAbsolutePosUpdate();
		}
		// 衝突判定
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