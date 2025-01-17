
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
#include "../Component/PlayerMovement.h"

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
			auto playerMovement = m_Player->AddComponent<AK_Game::PlayerMovement>();
			playerMovement->SetNormalAccel(XMVectorSet(10.0f, 5.0f, 10.0f, 0.0f));
			playerMovement->SetAirResistance(XMVectorSet(0.1f, 0.1f, 0.1f, 0.0f));	// さすがに高すぎ

			ActorSet::CreateDebugAxis(m_Player);
		}
		{
			auto testmodel = this->AddChild<AK_Base::Actor>(L"tester2");
			auto transform = testmodel->AddComponent<AK_Base::Transform>();
			transform->SetPosition(-3.0f, 2.0f, 3.0f);
			auto meshRender = testmodel->AddComponent<AK_Base::MeshRender>(L"resource/testData/testBox.glb");
			meshRender->SetShader("BasicRed");

			ActorSet::CreateDebugAxis(testmodel);
		}


		// カメラの準備
		m_Camera = std::make_unique<Camera::Camera>();

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
	GameMainScene::~GameMainScene()
	{

	}

	//--------------------------------------------------------------------------------------
	void GameMainScene::Update(const double& totalTime, const float& elapsedTime)
	{


		// シェーダーにVP行列をセット
		auto shaderM = Shader::ShaderManager::GetInstance();
		shaderM->SetVPMatrix(*m_Camera->GetView(), *m_Camera->GetProjection());

		Scene::Update(totalTime, elapsedTime);
	}

}