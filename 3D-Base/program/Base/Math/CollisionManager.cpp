
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Փ˔�������Ȃ�Collider�R���|�[�l���g���Ǘ�����N���X
// �V���O���g���N���X
// 
// �����	: amateurK
// �쐬��	: 2025/01/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "CollisionManager.h"

namespace AK_Base {
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

	}

}