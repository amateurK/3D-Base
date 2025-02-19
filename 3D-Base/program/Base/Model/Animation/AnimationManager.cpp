
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �A�j���[�V�����f�[�^���Ǘ�����}�l�[�W���[�N���X
// �V���O���g���N���X
// 
// �����	: amateurK
// �쐬��	: 2025/02/17
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
		// ���b�V�����쐬�ς݂����`�F�b�N
		auto itr = m_AnimationData.find(filePath);
		if (itr != m_AnimationData.end())
		{
			// �쐬�ς�
			return &itr->second;
		}
		else
		{
			// �V�K�쐬
			if (FAILED(m_AnimationData[filePath].LoadAnimation(filePath)))
			{
				throw std::exception("�A�j���[�V�����̓ǂݍ��݂Ɏ��s���܂����B");
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