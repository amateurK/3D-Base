
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// テスト用クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/04/22
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "TestScene.h"
#include "../../Base/Model/ModelActor.h"
#include "../Piece/Piece.h"

namespace Scene {

	TestScene::TestScene()
	{
		auto myGame((MyGame*)&AK_Base::BaseWindow::GetInstance());

		//auto testobj = new AK_Base::ModelActor(Game->GetBasicShader());
		//Game->GetRootActor()->AddChild(testobj);

		auto piece1 = new Piece::Piece(myGame->GetTestShader(), L"no.1", L"resource/testData/Sphere.fbx");
		myGame->GetRootActor()->AddChild(piece1);
		piece1->SetPosition(-3.0f, 0.0f, 3.0f);

		auto piece2 = new Piece::Piece(myGame->GetTestShader(), L"no.2", L"resource/testData/Sphere.fbx");
		myGame->GetRootActor()->AddChild(piece2);
		piece2->SetPosition(3.0f, 0.0f, 3.0f);


		// カメラの準備
		m_Camera = std::make_unique<Camera::Camera>();

		//const XMVECTOR eye = { 0.0f, 1.0f, -5.0f, 0.0f };
		//const XMVECTOR at = { 0.0f, 1.0f, 0.0f, 0.0f };
		const XMVECTOR eye = { 2.0f, 2.0f, -3.0f, 0.0f };
		const XMVECTOR at = { 0.0f, 0.0f, 3.0f, 0.0f };
		const XMVECTOR up = { 0.0f, 1.0f, 0.0f, 0.0f };
		m_Camera->SetCamera(eye, at, up);

		auto windowSize = myGame->GetWindowSize();
		m_Camera->SetScreen(XM_PIDIV2, static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y));

		// シェーダーにセット
		auto shader = myGame->GetTestShader();
		shader->SetViewMatrix(m_Camera->GetView());
		shader->SetProjectionMatrix(m_Camera->GetProjection());
	}
	//--------------------------------------------------------------------------------------
	TestScene::~TestScene()
	{
		
	}

	//--------------------------------------------------------------------------------------
	void TestScene::Move(const double& totalTime, const float& elapsedTime)
	{
		// カメラ回転テスト
		{
			// キー入力の検知
			bool up = (GetAsyncKeyState('W') & 0x8000) == 0x8000;
			bool down = (GetAsyncKeyState('S') & 0x8000) == 0x8000;
			bool left = (GetAsyncKeyState('A') & 0x8000) == 0x8000;
			bool right = (GetAsyncKeyState('D') & 0x8000) == 0x8000;
			bool zoomIn = (GetAsyncKeyState('Z') & 0x8000) == 0x8000;
			bool zoomOut = (GetAsyncKeyState('X') & 0x8000) == 0x8000;

			// あとでつくる
		}

		Scene::Move(totalTime, elapsedTime);
	}


}