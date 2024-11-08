#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// テスト用クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/04/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Scene.h"
#include "../../Base/Camera/DebugCamera.h"

namespace Scene {
	class TestScene : public Scene
	{
	private:

		/// @brief カメラクラス
		std::unique_ptr<Camera::DebugCamera> m_Camera;

	public:
		/// @brief コンストラクタ
		TestScene();
		/// @brief デストラクタ
		virtual ~TestScene();

		/// @brief シーンの更新
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のMove()からの経過時間（秒）
		virtual void Move(const double& totalTime, const float& elapsedTime) override;


	};
}