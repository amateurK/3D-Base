
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// アニメーションデータを管理するマネージャークラス
// シングルトンクラス
// 
// 製作者	: amateurK
// 作成日	: 2025/02/17
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "AnimationManager.h"

namespace Anim {

	AnimationManager* AnimationManager::Instance = nullptr;

	AnimationManager::AnimationManager()
	{
		m_AnimationData.clear();
	}

	//--------------------------------------------------------------------------------------
	AnimationManager::~AnimationManager()
	{
		ClearAllAnimation();
	}

	//--------------------------------------------------------------------------------------
	AnimationClip* AnimationManager::CreateAnimation(const std::wstring& filePath)
	{
		// メッシュが作成済みかをチェック
		auto itr = m_AnimationData.find(filePath);
		if (itr != m_AnimationData.end())
		{
			// 作成済み
			return &itr->second;
		}
		else
		{
			// 新規作成
			if (FAILED(m_AnimationData[filePath].LoadAnimation(filePath)))
			{
				throw std::exception("アニメーションの読み込みに失敗しました。");
				return nullptr;
			}
			return &m_AnimationData[filePath];
		}
	}

	//--------------------------------------------------------------------------------------
	void AnimationManager::ClearAnimation(const std::wstring& filePath)
	{
		auto itr = m_AnimationData.find(filePath);
		if (itr != m_AnimationData.end())
		{
			itr->second.ClearAnimation();
			m_AnimationData.erase(itr);
		}
	}

	//--------------------------------------------------------------------------------------
	void AnimationManager::ClearAllAnimation()
	{
		for (auto& anim : m_AnimationData)
		{
			anim.second.ClearAnimation();
		}
		m_AnimationData.clear();
	}
}