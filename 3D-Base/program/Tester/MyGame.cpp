//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �e�X�g�p
// �Q�[���{��
// BaseWindow���p��
// 
// �����	: amateurK
// �쐬��	: 2024/03/06
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "MyGame.h"
#include "Scene/TestScene.h"
#include "Base/Model/Mesh/MeshManager.h"
#include "Base/Shader/BasicShader.h"
#include "Base/Shader/LambertShader.h"


// �{�̂𐶐�
MyGame Game;


MyGame::MyGame()
	: AK_Base::BaseWindow()
{

}
MyGame::~MyGame()
{
	m_TestShader.reset();

	// �}�l�[�W���[�̔j��
	Mesh::MeshManager::Destroy();
}

//--------------------------------------------------------------------------------------
void MyGame::CreateActor()
{
	// �V�F�[�_�[�̏���
	m_TestShader = std::make_unique<Shader::LambertShader>();


	// �}�l�[�W���[�̐���
	Mesh::MeshManager::Create();


	// �e�X�g�p�̃V�[���𐶐�
	auto testScene = new Scene::TestScene();
	m_RootActor->AddChild(testScene);
}