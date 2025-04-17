#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ゲームのメインシーンのクラス
// 
// 製作者	: amateurK
// 作成日	: 2024/12/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Scene.h"
#include "Base/Component/Camera.h"

namespace Scene {
	class GameMainScene : public Scene
	{
	private:

		/// @brief カメラクラス
		AK_Base::Camera* m_Camera;

		// プレイヤーのアクター
		AK_Base::Actor* m_Player;

	public:
		/// @brief コンストラクタ
		GameMainScene(std::wstring name = L"unnamed");
		/// @brief デストラクタ
		virtual ~GameMainScene();

		/// @brief シーンの更新
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のUpdate()からの経過時間（秒）
		virtual void Update(const double& totalTime, const float& elapsedTime) override;


	};
}
