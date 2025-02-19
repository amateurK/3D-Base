#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// アニメーションデータを管理するマネージャークラス
// シングルトンクラス
// 
// 製作者	: amateurK
// 作成日	: 2025/02/17
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "AnimationClip.h"

namespace Anim {

	/// @brief アニメーションデータを管理するマネージャークラス
	class AnimationManager
	{
	private:

		/// @brief コンストラクタ
		AnimationManager();
		/// @brief デストラクタ
		~AnimationManager();

		static AnimationManager* Instance;
	public:
		AnimationManager(AnimationManager&&) = delete;
		AnimationManager& operator=(AnimationManager&&) = delete;

		AnimationManager(AnimationManager const&) = delete;
		AnimationManager& operator=(AnimationManager const&) = delete;

		/// @brief このクラスのインスタンスを取得
		/// @return インスタンス
		static AnimationManager* GetInstance() {
			return Instance;
		}
		/// @brief インスタンスを生成
		static void Create() {
			if (Instance == nullptr) {
				Instance = new AnimationManager;
			}
			else {
				throw std::exception("AnimationManager is a singleton");
			}
		}
		/// @brief インスタンスの解放
		static void Destroy() {
			delete Instance;
			Instance = nullptr;
		}

	private:

		/// @brief アニメーションデータ
		/// @details キー : ファイルパス
		/// @details 値 : アニメーションデータ
		std::unordered_map<std::wstring, AnimationClip> m_AnimationData;

	public:

		/// @brief アニメーションの取得（読み込んでから取得）
		/// @param filePath ファイルパス
		/// @return アニメーションへのポインタ
		AnimationClip* CreateAnimation(const std::wstring& filePath);

		/// @brief アニメーションの削除
		/// @param filePath ファイルパス
		void ClearAnimation(const std::wstring& filePath);

		/// @brief 全てのアニメーションの削除
		void ClearAllAnimation();
	};
}
