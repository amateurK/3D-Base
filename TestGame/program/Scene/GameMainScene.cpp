
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ゲームのメインシーンのクラス
// 
// 製作者	: amateurK
// 作成日	: 2024/12/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "GameMainScene.h"
#include "Base/Component/Transform.h"
#include "Base/Component/MeshRender.h"
#include "Base/Shader/ShaderManager.h"
#include "Base/ActorSet/DebugAxis.h"
#include "Base/Input/InputManager.h"
#include "Base/Component/Collider/SphereCollider.h"
#include "Base/Input/InputManager.h"
#include "../Component/Entity/Player/PlayerMovement.h"

using namespace DirectX;

namespace Scene {

	GameMainScene::GameMainScene(std::wstring name)
		: Scene(name)
	{
		auto myGame(&AK_Base::BaseWindow::GetInstance());


		// モデルの作成
		{
			m_Player = this->AddChild<AK_Base::Actor>(L"player");
			auto transform = m_Player->AddComponent<AK_Base::Transform>();
			transform->Scale(3.0f);
			transform->SetPosition(3.0f, 0.0f, 3.0f);
			auto meshRender = m_Player->AddComponent<AK_Base::MeshRender>(L"resource/testData/AvatarSample_A.vrm");
			meshRender->SetShader("LambertShader");
			//auto playerMovement = m_Player->AddComponent<AK_Game::PlayerMovement>();
			//playerMovement->SetNormalAccel(10.0f, 5.0f, 10.0f);
			//playerMovement->SetAirResistance(0.1f);	// さすがに高すぎ
			auto collider = m_Player->AddComponent<AK_Base::SphereCollider>(AK_Math::Sphere3());

			ActorSet::CreateDebugAxis(m_Player);
		}
		{
			auto testmodel = this->AddChild<AK_Base::Actor>(L"tester2");
			auto transform = testmodel->AddComponent<AK_Base::Transform>();
			transform->SetPosition(-3.0f, 2.0f, 3.0f);
			auto meshRender = testmodel->AddComponent<AK_Base::MeshRender>(L"../3D-Base/BasicModel/Cube.glb");
			meshRender->SetShader("BasicRed");

			ActorSet::CreateDebugAxis(testmodel);
		}
		for (int i = 0; i < 10; i++) {
			auto testmodel = this->AddChild<AK_Base::Actor>(L"Target" + i);
			auto transform = testmodel->AddComponent<AK_Base::Transform>();
			transform->SetPosition(-3.0f, 2.0f, 3.0f);
			auto meshRender = testmodel->AddComponent<AK_Base::MeshRender>(L"../3D-Base/BasicModel/ICOSphere.glb");
			meshRender->SetShader("BasicRed");

			auto collider = m_Player->AddComponent<AK_Base::SphereCollider>(AK_Math::Sphere3(XMVectorZero(), 1.0f));
			collider->SetOnCollision([=](AK_Base::Collider* const other) {
				transform->SetPosition(, 2.0f, 3.0f)
				});
		}

		// カメラの準備
		{
			auto testmodel = this->AddChild<AK_Base::Actor>(L"camera");
			auto transform = testmodel->AddComponent<AK_Base::Transform>();
			transform->SetPosition(0.0f, 3.0f, -6.5f);
			m_Camera = testmodel->AddComponent<AK_Base::Camera>();
			auto windowSize = myGame->GetWindowSize();
			m_Camera->SetScreen(XM_PIDIV2, static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y));
			auto playerMovement = testmodel->AddComponent<AK_Game::PlayerMovement>();
			playerMovement->SetNormalAccel(20.0f, 10.0f, 20.0f);
			playerMovement->SetAirResistance(0.1f);	// さすがに高すぎ
		}

		// マウスのカーソルを中央に移動して非表示
		{
			auto InputM = AK_Base::InputManager::GetInstance();
			InputM->SetCursorCenter();
			InputM->SetShowCursor(FALSE);
		}

		// シェーダーにVP行列をセット
		auto shaderM = Shader::ShaderManager::GetInstance();
		shaderM->SetVPMatrix(*m_Camera->GetView(), *m_Camera->GetProjection());


	}
	//--------------------------------------------------------------------------------------
	GameMainScene::~GameMainScene()
	{

	}

	//--------------------------------------------------------------------------------------
	void GameMainScene::Update(const double& totalTime, const float& elapsedTime)
	{
		auto InputM = AK_Base::InputManager::GetInstance();
		// マウスカーソルの表示・非表示切り替え
		{
			if (InputM->IsKeyNowPressed(DIK_TAB)) {
				InputM->SetShowCursor(!InputM->GetIsCursorShown());
			}
		}

		// カメラの移動
		{
			// 視点移動はマウスが非表示の時のみ
			if (!InputM->GetIsCursorShown())
			{
				// 移動量を取得
				const auto& delta = InputM->GetMouseMove();

				// カメラの回転
				auto trans = m_Camera->GetActor()->GetTransform();
				trans->RotateY(delta.x * 0.0015f);
				trans->RotateLocalX(delta.y * 0.0015f);

				// カーソルを中央に戻す
				InputM->SetCursorCenter();
			}
		}

		// シェーダーにVP行列をセット
		auto shaderM = Shader::ShaderManager::GetInstance();
		shaderM->SetVPMatrix(*m_Camera->GetView(), *m_Camera->GetProjection());

		Scene::Update(totalTime, elapsedTime);
	}

}