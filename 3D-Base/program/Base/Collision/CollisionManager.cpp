
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
		// Colliderの更新
		for (auto& collider : m_IsCollideCache)
		{
			collider.first->CheckAbsolutePosUpdate();
			// 衝突しているColliderのリストをクリア
			collider.second.first.clear();
			collider.second.second.clear();
		}

		// 衝突判定を行うColliderをvectorに入れる
		std::vector<Collider*> colliders;
		for (auto& [collider, dummy] : m_IsCollideCache)
		{
			if (collider->GetActor()->GetEffectiveStatus() == ActorStatus::ACTION)
			{
				colliders.push_back(collider);
			}
		}

		// 衝突判定
		// 重複を回避
		for (size_t i = 0; i < colliders.size(); ++i)
		{
			for (size_t j = i + 1; j < colliders.size(); ++j)
			{
				Collider* a = colliders[i];
				Collider* b = colliders[j];

				if (a->CheckCollision(b))
				{
					// 衝突時の処理を実行
					a->OnCollision(b);
					b->OnCollision(a);

					m_IsCollideCache[a].first.insert(b);
					m_IsCollideCache[b].first.insert(a);
				}
				else
				{
					m_IsCollideCache[a].second.insert(b);
					m_IsCollideCache[b].second.insert(a);
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