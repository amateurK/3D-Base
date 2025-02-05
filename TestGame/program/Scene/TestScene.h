#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// テスト用クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/04/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Scene.h"
#include "Base/Component/Camera.h"

namespace Scene {
	class TestScene : public Scene
	{
	private:

		/// @brief カメラクラス
		AK_Base::Camera* m_Camera;

	public:
		/// @brief コンストラクタ
		TestScene(std::wstring name = L"unnamed");
		/// @brief デストラクタ
		virtual ~TestScene();

		/// @brief シーンの更新
		/// @param totalTime : アプリケーション起動からの経過時間（秒）
		/// @param elapsedTime : 前回のUpdate()からの経過時間（秒）
		virtual void Update(const double& totalTime, const float& elapsedTime) override;


	};
}