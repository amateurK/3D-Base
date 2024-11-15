//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// テスト用
// ゲーム本体
// BaseWindowを継承
// 
// 製作者	: amateurK
// 作成日	: 2024/03/06
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "MyGame.h"
#include "Scene/TestScene.h"
#include "Base/Model/Mesh/MeshManager.h"
#include "Base/Shader/BasicShader.h"
#include "Base/Shader/LambertShader.h"


// 本体を生成
MyGame Game;


MyGame::MyGame()
	: AK_Base::BaseWindow()
{

}
MyGame::~MyGame()
{
	m_TestShader.reset();

	// マネージャーの破棄
	Mesh::MeshManager::Destroy();
}

//--------------------------------------------------------------------------------------
void MyGame::CreateActor()
{
	// シェーダーの準備
	m_TestShader = std::make_unique<Shader::LambertShader>();


	// マネージャーの生成
	Mesh::MeshManager::Create();


	// テスト用のシーンを生成
	auto testScene = new Scene::TestScene();
	m_RootActor->AddChild(testScene);
}