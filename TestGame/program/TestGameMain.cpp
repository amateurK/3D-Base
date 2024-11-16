
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���C���֐�
// 
// �����	: amateurK
// �쐬��	: 2024/11/16
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "TestGameMain.h"
#include "Base/Framework.h"
#include "Scene/TestScene.h"
#include "Base/Actor.h"


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{

	// �t���[�����[�N���ɏ�������C
	return FrameworkMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 
		[&](AK_Base::Actor* root) {

		// �V�[���̐���
		// �e�X�g�p�̃V�[���𐶐�
		auto testScene = new Scene::TestScene();
		root->AddChild(testScene);
		});
}