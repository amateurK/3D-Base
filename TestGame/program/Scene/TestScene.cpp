
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// テスト用クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/04/22
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "TestScene.h"
#include "Base/Model/ModelActor.h"
#include "../Piece/Piece.h"
#include "Base/Input/InputManager.h"
#include "Base/Component/Transform.h"
#include "Base/Component/MeshRender.h"

namespace Scene {

	TestScene::TestScene()
		: Scene()
	{
		this->SetStatus(AK_Base::ActorStatus::ACTION);
		auto myGame(&AK_Base::BaseWindow::GetInstance());

		//auto testobj = new AK_Base::ModelActor(Game->GetBasicShader());
		//Game->GetRootActor()->AddChild(testobj);

		//auto piece1 = new Piece::Piece(myGame->GetTestShader(), L"no.1", L"resource/testData/Alicia_FBX/Alicia_solid_Unity.FBX");
		//this->AddChild(piece1);
		//piece1->SetPosition(-3.0f, 0.0f, 3.0f);
		//piece1->Scaling(0.05f);

		auto piece1 = this->AddChild<AK_Base::Actor>(L"tester");
		piece1->AddComponent<AK_Base::Transform>();
		auto meshRender = piece1->AddComponent<AK_Base::MeshRender>(L"resource/testData/AvatarSample_A.vrm");
		meshRender->SetShader(myGame->GetTestShader());


		auto piece2 = this->AddChild<Piece::Piece>(myGame->GetTestShader(), L"no.2", L"resource/testData/AvatarSample_A.vrm");
		piece2->SetPosition(3.0f, 0.0f, 3.0f);
		piece2->Scaling(6.0f);


		// カメラの準備
		m_Camera = std::make_unique<Camera::Camera>();

		//const XMVECTOR eye = { 0.0f, 1.0f, -5.0f, 0.0f };
		//const XMVECTOR at = { 0.0f, 1.0f, 0.0f, 0.0f };
		const XMVECTOR eye = { 0.0f, 4.0f, -2.0f, 0.0f };
		const XMVECTOR at = { 0.0f, 4.0f, 3.0f, 0.0f };
		const XMVECTOR up = { 0.0f, 1.0f, 0.0f, 0.0f };
		m_Camera->SetCamera(&eye, &at, &up);

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
	void TestScene::Update(const double& totalTime, const float& elapsedTime)
	{
		// カメラ回転テスト
		{
			// キー入力の検知
			auto input = AK_Base::InputManager::GetInstance();
			bool w = input->IsKeyPressed(DIK_W);
			bool s = input->IsKeyPressed(DIK_S);
			bool a = input->IsKeyPressed(DIK_A);
			bool d = input->IsKeyPressed(DIK_D);
			bool z = input->IsKeyPressed(DIK_Z);
			bool x = input->IsKeyPressed(DIK_X);

			// カメラの試運転
			float speed = 2.0f;
			float front = (float)(w - s) * elapsedTime * speed;
			float right = (float)(d - a) * elapsedTime * speed;
			float up = (float)(z - x) * elapsedTime * speed;
			m_Camera->MoveWithViewpoint(front, right, up);
		}
		// 移動テスト
		{
			// キー入力の検知
			auto input = AK_Base::InputManager::GetInstance();
			bool w = input->IsKeyPressed(DIK_UP);
			bool s = input->IsKeyPressed(DIK_DOWN);
			bool a = input->IsKeyPressed(DIK_LEFT);
			bool d = input->IsKeyPressed(DIK_RIGHT);
			bool z = input->IsKeyPressed(DIK_O);
			bool x = input->IsKeyPressed(DIK_P);

			// 試運転
			float speed = 2.0f;
			float front = (float)(w - s) * elapsedTime * speed;
			float right = (float)(d - a) * elapsedTime * speed;
			float up = (float)(z - x) * elapsedTime * speed;
			auto actor = AK_Base::BaseWindow::GetInstance().GetRootActor()->SearchName(L"tester");;
			actor->GetComponent<AK_Base::Transform>()->Move(front, right, up);
		}
		// マウステスト
		{
			auto input = AK_Base::InputManager::GetInstance();
			bool tab = input->IsKeyNowPressed(DIK_TAB);
			if (tab) {
				input->CursorClipByWindow(!input->GetIsCursorClippedByWindow());
			}
			bool c = input->IsKeyNowPressed(BUTTON_MOUSE0);
			if (c) {
				input->SetShowCursor(!input->GetIsCursorShown());
			}
			bool v = input->IsKeyNowPressed(BUTTON_MOUSE1);
			if (v) {
				input->SetCursorCenter();
			}
			bool b = input->IsKeyNowPressed(BUTTON_MOUSE2);
			if (b) {
				POINT nowPos = input->GetCursorPosition();
				nowPos.x += 10;
				nowPos.y += 10;
				input->SetCursorPosition(nowPos);
			}
		}

		// シェーダーにview行列を入れる
		auto myGame(&AK_Base::BaseWindow::GetInstance());
		auto shader = myGame->GetTestShader();
		shader->SetViewMatrix(m_Camera->GetView());

		Scene::Update(totalTime, elapsedTime);
	}


}