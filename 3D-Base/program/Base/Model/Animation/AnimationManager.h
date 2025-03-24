#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �A�j���[�V�����f�[�^���Ǘ�����}�l�[�W���[�N���X
// �V���O���g���N���X
// 
// �����	: amateurK
// �쐬��	: 2025/02/17
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "AnimationClip.h"

namespace Anim {

	/// @brief �A�j���[�V�����f�[�^���Ǘ�����}�l�[�W���[�N���X
	class AnimationManager
	{
	private:

		/// @brief �R���X�g���N�^
		AnimationManager();
		/// @brief �f�X�g���N�^
		~AnimationManager();

		static AnimationManager* Instance;
	public:
		AnimationManager(AnimationManager&&) = delete;
		AnimationManager& operator=(AnimationManager&&) = delete;

		AnimationManager(AnimationManager const&) = delete;
		AnimationManager& operator=(AnimationManager const&) = delete;

		/// @brief ���̃N���X�̃C���X�^���X���擾
		/// @return �C���X�^���X
		static AnimationManager* GetInstance() {
			return Instance;
		}
		/// @brief �C���X�^���X�𐶐�
		static void Create() {
			if (Instance == nullptr) {
				Instance = new AnimationManager;
			}
			else {
				throw std::exception("AnimationManager is a singleton");
			}
		}
		/// @brief �C���X�^���X�̉��
		static void Destroy() {
			delete Instance;
			Instance = nullptr;
		}

	private:

		/// @brief �A�j���[�V�����f�[�^
		/// @details �L�[ : �t�@�C���p�X
		/// @details �l : �A�j���[�V�����f�[�^
		std::unordered_map<std::wstring, AnimationClip> m_AnimationData;

	public:

		/// @brief �A�j���[�V�����̎擾�i�ǂݍ���ł���擾�j
		/// @param filePath �t�@�C���p�X
		/// @return �A�j���[�V�����ւ̃|�C���^
		AnimationClip* CreateAnimation(const std::wstring& filePath);

		/// @brief �A�j���[�V�����̍폜
		/// @param filePath �t�@�C���p�X
		void ClearAnimation(const std::wstring& filePath);

		/// @brief �S�ẴA�j���[�V�����̍폜
		void ClearAllAnimation();
	};
}
