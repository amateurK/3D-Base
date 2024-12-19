
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// メイン関数
// 
// 製作者	: amateurK
// 作成日	: 2024/11/16
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "TestGameMain.h"
#include "Base/Framework.h"
#include "Scene/TestScene.h"
#include "Scene/FastCheck.h"
#include "Base/Actor.h"


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{

	// フレームワーク側に処理を一任
	return FrameworkMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow,
		[&](AK_Base::Actor* root) {

			// シーンの生成
			{
				auto scene = new Scene::TestScene(L"TestScene");
				root->AddChild(scene);
				scene->SetStatus(AK_Base::ActorStatus::ACTION);
			}
			{
				auto scene = new Scene::FastCheck(L"SpeedCheck");
				root->AddChild(scene);
				//scene->SetStatus(AK_Base::ActorStatus::ACTION);
			}
		});
}