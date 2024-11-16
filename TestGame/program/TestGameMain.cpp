
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
#include "Base/Actor.h"

// Indicates to hybrid graphics systems to prefer the discrete part by default
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{

	// フレームワーク側に処理を一任
	FrameworkMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow, [&](AK_Base::Actor* root) {

		// シーンの生成
		// テスト用のシーンを生成
		auto testScene = new Scene::TestScene();
		root->AddChild(testScene);
		});
}