
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
#include "Base/Tools/Random.h"
#include "Base/Audio/AudioManager.h"
#include "../Component/Entity/Player/PlayerMovement.h"
#include "../Component/Entity/Bullet/SimpleBullet.h"

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
			transform->Scale(1.0f);
			transform->SetPosition(3.0f, 0.0f, 3.0f);
			//auto meshRender = m_Player->AddComponent<AK_Base::MeshRender>(L"resource/testData/AvatarSample_A.vrm");
			//meshRender->SetShader("LambertShader");
			auto playerMovement = m_Player->AddComponent<AK_Game::PlayerMovement>();
			playerMovement->SetNormalAccel(20.0f, 10.0f, 20.0f);
			playerMovement->SetAirResistance(0.1f);	// さすがに高すぎ
			auto collider = m_Player->AddComponent<AK_Base::SphereCollider>(AK_Math::Sphere3(XMVectorZero(), 0.5f));

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
		for (int i = 0; i < 20; i++)
		{
			auto testmodel = this->AddChild<AK_Base::Actor>(L"Target" + std::to_wstring(i));
			auto transform = testmodel->AddComponent<AK_Base::Transform>();
			// お互いに当たって移動するため初期位置は不要
			auto meshRender = testmodel->AddComponent<AK_Base::MeshRender>(L"../3D-Base/BasicModel/ICOSphere.glb");
			meshRender->SetShader("BasicGreen");

			auto collider = testmodel->AddComponent<AK_Base::SphereCollider>(AK_Math::Sphere3(XMVectorZero(), 1.0f));
			collider->SetOnCollision([=](AK_Base::Collider* const other) {
				transform->SetPosition(
					(float)Tools::GetRandom(-50, 50),
					(float)Tools::GetRandom(-10, 10),
					(float)Tools::GetRandom(-50, 50));
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

		// 音源の読み込み
		{
			auto audioM = AK_Base::AudioManager::GetInstance();
			audioM->SetMasterVolume(0.02f);

			audioM->SetBGMVolume(1.0f);
			audioM->RoadSoundFile(0, L"resource/testSound/ZONE_-X13-.mp3");

			audioM->SetSEVolume(1.0f);
			audioM->RoadSoundFile(100, L"resource/testSound/銃声._8ビット風._「バーン」.mp3");
			audioM->RoadSoundFile(101, L"resource/testSound/ショット.mp3");
			audioM->RoadSoundFile(102, L"resource/testSound/ブースタージャンプ2.mp3");

			//audioM->ChangeBGM(0);
		}
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
			auto cameraTrans = m_Camera->GetActor()->GetTransform();
			auto playerTrans = m_Player->GetTransform();
			// 視点移動はマウスが非表示の時のみ
			if (!InputM->GetIsCursorShown())
			{
				// 移動量を取得
				const auto& delta = InputM->GetMouseMove();

				// カメラの回転
				cameraTrans->RotateY(delta.x * 0.0015f);
				cameraTrans->RotateLocalX(delta.y * 0.0015f);

				// カーソルを中央に戻す
				InputM->SetCursorCenter();
			}

			// カメラをプレイヤーに追従
			cameraTrans->SetPosition(playerTrans->GetPosition() + DirectX::XMVectorSet(0.0f, 1.6f, 0.0f, 0.0f));
			cameraTrans->Move(-2.0f, 0.0f, 0.0f);

			// プレイヤーをカメラの向きに合わせる
			auto cameraMat = DirectX::XMMatrixRotationQuaternion(cameraTrans->GetRotation());
			auto cameraForward = cameraMat.r[2];	// カメラの向きを取得
			cameraForward *= DirectX::XMVectorSet(-1.0f, 0.0f, 1.0f, 0.0f);	// Yを0、Xを反転
			cameraForward = XMVector3Normalize(cameraForward);
			playerTrans->SetRotation(XMQuaternionRotationMatrix(
				XMMatrixLookToLH(XMVectorZero(), cameraForward, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f))));

		}

		// 弾を撃つ（テスト）
		{
			if (InputM->IsKeyNowPressed(BUTTON_MOUSE0))
			{
				auto bullet = this->AddChild<AK_Base::Actor>(L"bullet" + std::to_wstring(totalTime));
				auto transform = bullet->AddComponent<AK_Base::Transform>();
				transform->SetPosition(m_Camera->GetActor()->GetTransform()->GetPosition());
				transform->SetRotation(m_Camera->GetActor()->GetTransform()->GetRotation());
				transform->Move(DirectX::XMVectorSet(0.0f, 0.0f, 5.0f, 0.0f));
				auto meshRender = bullet->AddComponent<AK_Base::MeshRender>(L"../3D-Base/BasicModel/ICOSphere.glb");
				meshRender->SetShader("BasicRed");

				auto collider = bullet->AddComponent<AK_Base::SphereCollider>(AK_Math::Sphere3(XMVectorZero(), 1.0f));
				collider->SetOnCollision([=](AK_Base::Collider* const other) {
					bullet->SetStatus(AK_Base::ActorStatus::DEAD);
					});
				auto bulletMovement = bullet->AddComponent<AK_Game::SimpleBullet>();
				bulletMovement->SetSpeed(60.0f, 0.0f, 0.0f);
				bulletMovement->SetLifeTime(3.0f);

				// 音の再生
				auto audioM = AK_Base::AudioManager::GetInstance();
				//audioM->SetSEVolume(2.0f * (1.0f + sin(totalTime * 3.0f)));
				audioM->PlaySE(100, 0.5f);
				audioM->PlaySE(101, 0.7f);
				audioM->PlaySE(102, 0.7f);
			}
		}

		// シェーダーにVP行列をセット
		auto shaderM = Shader::ShaderManager::GetInstance();
		shaderM->SetVPMatrix(*m_Camera->GetView(), *m_Camera->GetProjection());

		Scene::Update(totalTime, elapsedTime);
	}

}