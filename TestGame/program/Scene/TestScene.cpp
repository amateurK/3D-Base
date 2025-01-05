//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// テスト用クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/04/22
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "TestScene.h"
#include "Base/Component/Transform.h"
#include "Base/Component/MeshRender.h"
#include "Base/Component/Collider.h"
#include "Base/Shader/ShaderManager.h"
#include "Base/ActorSet/DebugAxis.h"
#include "Base/Input/InputManager.h"

using namespace DirectX;

namespace Scene {

	TestScene::TestScene(std::wstring name)
		: Scene(name)
	{
		auto myGame(&AK_Base::BaseWindow::GetInstance());


		// モデルの作成
		{
			auto testmodel = this->AddChild<AK_Base::Actor>(L"tester");
			auto transform = testmodel->AddComponent<AK_Base::Transform>();
			transform->Scale(3.0f);
			transform->SetPosition(3.0f, 0.0f, 3.0f);
			auto meshRender = testmodel->AddComponent<AK_Base::MeshRender>(L"resource/testData/AvatarSample_A.vrm");
			meshRender->SetShader("LambertShader");
			auto collider = testmodel->AddComponent<AK_Base::Collider>();

			ActorSet::CreateDebugAxis(testmodel);
		}
		{
			auto testmodel = this->AddChild<AK_Base::Actor>(L"tester2");
			auto transform = testmodel->AddComponent<AK_Base::Transform>();
			transform->SetPosition(-3.0f, 2.0f, 3.0f);
			auto meshRender = testmodel->AddComponent<AK_Base::MeshRender>(L"resource/testData/testBox.glb");
			meshRender->SetShader("BasicRainbow");

			ActorSet::CreateDebugAxis(testmodel);
		}


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


		// シェーダーにVP行列をセット
		auto shaderM = Shader::ShaderManager::GetInstance();
		shaderM->SetVPMatrix(*m_Camera->GetView(), *m_Camera->GetProjection());
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
			auto actor = AK_Base::BaseWindow::GetInstance().GetRootActor()->SearchName(L"tester");
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
		// 軸依存の回転
		{
			// キー入力の検知
			bool i = (GetAsyncKeyState('I') & 0x8000) == 0x8000;
			bool k = (GetAsyncKeyState('K') & 0x8000) == 0x8000;
			bool j = (GetAsyncKeyState('J') & 0x8000) == 0x8000;
			bool l = (GetAsyncKeyState('L') & 0x8000) == 0x8000;
			bool u = (GetAsyncKeyState('U') & 0x8000) == 0x8000;

			// 試運転
			float speed = 2.0f;
			float right = (float)(j - l) * elapsedTime * speed;
			float up = (float)(i - k) * elapsedTime * speed;
			auto actor = AK_Base::BaseWindow::GetInstance().GetRootActor()->SearchName(L"tester");
			auto actor2 = AK_Base::BaseWindow::GetInstance().GetRootActor()->SearchName(L"tester2");

			actor->GetComponent<AK_Base::Transform>()->Rotate(XMVECTOR{ 0.0f, 1.0f, 0.0f, 1.0f }, right);
			actor->GetComponent<AK_Base::Transform>()->Rotate(XMVECTOR{ 1.0f, 0.0f, 0.0f, 1.0f }, up);
			if(u)actor->GetComponent<AK_Base::Transform>()->LookAtPosition(actor2->GetTransform()->GetPosition());
		}
		// シェーダーテスト
		{
			auto shaderM = Shader::ShaderManager::GetInstance();

			// ブロックの色変更（緑と青の間が変なのは未修正）
			float hue = fmodf((float)totalTime, 6.0f); // 色相を6分割 (0〜6)
			float r = std::max(0.0f, 2.0f - fabs(hue - 3.0f));
			float g = std::max(0.0f, 2.0f - fabs(hue - 1.0f));
			float b = std::max(0.0f, 2.0f - fabs(hue - 5.0f));
			auto shader = shaderM->GetShaderSet("BasicRainbow");
			shader->SetData<XMFLOAT4>("color", { r, g, b, 1.0f });
			auto shader2 = shaderM->GetShaderSet("LambertShader");
			//shader2->SetData<XMVECTOR>("lightDirection", XMVectorSet(0.0f, 0.0f, -1.0f, 1.0f));
			shader2->SetData<XMVECTOR>("lightDirection", XMVectorSet((float)cos(totalTime) * 10.0f, (float)sin(totalTime)* 10.0f, -1.0f, 1.0f));
		}

		// シェーダーにVP行列をセット
		auto shaderM = Shader::ShaderManager::GetInstance();
		shaderM->SetVPMatrix(*m_Camera->GetView(), *m_Camera->GetProjection());

		

		Scene::Update(totalTime, elapsedTime);
	}


}