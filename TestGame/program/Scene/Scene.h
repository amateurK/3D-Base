#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// シーンクラス
// 
// 製作者	: amateurK
// 作成日	: 2024/04/22
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Base/Actor.h"

namespace Scene {

	/// @brief シーンクラス
	class Scene :public AK_Base::Actor 
	{
	protected:
		/// @brief Update()の実行回数
		uint32_t m_Times;

	public:
		/// @brief コンストラクタ
		Scene(std::wstring name = L"unnamed");
		/// @brief デストラクタ
		virtual ~Scene();

		/// @brief シーンの更新
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のUpdate()からの経過時間（秒）
		virtual void Update(const double& totalTime, const float& elapsedTime) override;


		/// @brief ACTION状態に移行
		virtual void ChangeAction() {
			m_Status = AK_Base::ActorStatus::ACTION;
		}
		/// @brief REST状態に以降
		virtual void ChangeRest() {
			m_Status = AK_Base::ActorStatus::REST;
		}
	};
}
