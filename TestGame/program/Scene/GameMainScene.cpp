
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

namespace Scene {

	GameMainScene::GameMainScene()
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





	}
	//--------------------------------------------------------------------------------------
	GameMainScene::~GameMainScene()
	{

	}

	//--------------------------------------------------------------------------------------
	void GameMainScene::Update(const double& totalTime, const float& elapsedTime)
	{


		Scene::Update(totalTime, elapsedTime);
	}

}