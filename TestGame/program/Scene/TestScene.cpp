
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
#include "Base/Shader/ShaderManager.h"
#include "Base/ActorSet/DebugAxis.h"

namespace Scene {

	TestScene::TestScene()
		: Scene()
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

			ActorSet::CreateDebugAxis(testmodel);
		}
		{
			auto testmodel = this->AddChild<AK_Base::Actor>(L"tester2");
			auto transform = testmodel->AddComponent<AK_Base::Transform>();
			transform->SetPosition(-3.0f, 2.0f, 3.0f);
			auto meshRender = testmodel->AddComponent<AK_Base::MeshRender>(L"resource/testData/testBox.glb");
			meshRender->SetShader("BasicShader");

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
			bool w = (GetAsyncKeyState('W') & 0x8000) == 0x8000;
			bool s = (GetAsyncKeyState('S') & 0x8000) == 0x8000;
			bool a = (GetAsyncKeyState('A') & 0x8000) == 0x8000;
			bool d = (GetAsyncKeyState('D') & 0x8000) == 0x8000;
			bool z = (GetAsyncKeyState('Z') & 0x8000) == 0x8000;
			bool x = (GetAsyncKeyState('X') & 0x8000) == 0x8000;

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
			bool w = (GetAsyncKeyState(VK_UP) & 0x8000) == 0x8000;
			bool s = (GetAsyncKeyState(VK_DOWN) & 0x8000) == 0x8000;
			bool a = (GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000;
			bool d = (GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000;
			bool z = (GetAsyncKeyState('O') & 0x8000) == 0x8000;
			bool x = (GetAsyncKeyState('P') & 0x8000) == 0x8000;

			// 試運転
			float speed = 2.0f;
			float front = (float)(w - s) * elapsedTime * speed;
			float right = (float)(d - a) * elapsedTime * speed;
			float up = (float)(z - x) * elapsedTime * speed;
			auto actor = AK_Base::BaseWindow::GetInstance().GetRootActor()->SearchName(L"tester");
			actor->GetComponent<AK_Base::Transform>()->Move(front, right, up);
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

		// シェーダーにVP行列をセット
		auto shaderM = Shader::ShaderManager::GetInstance();
		shaderM->SetVPMatrix(*m_Camera->GetView(), *m_Camera->GetProjection());

		Scene::Update(totalTime, elapsedTime);
	}


}