#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 速度検証用シーン
// 
// 製作者	: amateurK
// 作成日	: 2024/12/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Scene.h"
#include "Base/Tools/StepTimer.h"

namespace Scene {
	class FastCheck : public Scene
	{
	private:
		/// @brief 時間経過を管理するステップタイマー
		DX::StepTimer m_StepTimer;


	public:
		/// @brief コンストラクタ
		FastCheck();
		/// @brief デストラクタ
		virtual ~FastCheck();

		/// @brief シーンの更新
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のUpdate()からの経過時間（秒）
		virtual void Update(const double& totalTime, const float& elapsedTime) override;


	};
}