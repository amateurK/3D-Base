
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
		// 衝突判定
		// TODO : すでに調査済みのものはやらなくてもいいようにしてもいいかも
		for (auto& collider : m_IsCollideCache)
		{
			for (auto& other : m_IsCollideCache)
			{
				// 同じもの同士の場合無視
				if (collider.first == other.first)
				{
					continue;
				}
				// 衝突判定
				if (collider.first->CheckCollision(other.first))
				{
					collider.first->OnCollision(other.first);

					// 衝突しているColliderを登録
					collider.second.first.insert(other.first);
				}
				else
				{
					// 衝突していないColliderを登録
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