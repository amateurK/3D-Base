
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 衝突判定を奥なうColliderコンポーネントを管理するクラス
// シングルトンクラス
// 
// 製作者	: amateurK
// 作成日	: 2025/01/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "CollisionManager.h"

namespace AK_Base {
	//--------------------------------------------------------------------------------------
	CollisionManager::CollisionManager()
	{
		m_ColliderList.clear();
		m_CheckList.clear();
	}

	//--------------------------------------------------------------------------------------
	CollisionManager::~CollisionManager()
	{

		for (auto& list : m_ColliderList) {
			list.second.clear();
		}
		m_ColliderList.clear();
		m_CheckList.clear();
	}

	//---------------------------------------------------------------------------------------------
	void CollisionManager::AddColliderList(const std::string& listName, Collider* ptr)
	{
		m_ColliderList[listName].push_back(ptr);
	}

	//---------------------------------------------------------------------------------------------
	void CollisionManager::AddCkeckList(const std::string& listName1, const std::string& listName2)
	{
		m_CheckList.push_back(std::pair<std::string, std::string>(listName1, listName2));
	}

	//---------------------------------------------------------------------------------------------
	void CollisionManager::RemoveCheckList(const std::string& listName1, const std::string& listName2)
	{
		std::pair<std::string, std::string> pair(listName1, listName2);
		for (auto itr = m_CheckList.begin(); itr != m_CheckList.end();) {
			if ((*itr) == pair) {
				itr = m_CheckList.erase(itr);
			}
			else {
				itr++;
			}
		}
	}

}