
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
#include "Scene/FastCheck.h"
#include "Scene/GameMainScene.h"
#include "Base/Actor.h"


//#define SPEED_CHECK


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{

	// �t���[�����[�N���ɏ�������C
	return FrameworkMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow,
		[&](AK_Base::Actor* root) {

			// �V�[���̐���
#ifdef SPEED_CHECK
			{
				auto scene = new Scene::FastCheck(L"SpeedCheck");
				root->AddChild(scene);
				scene->SetStatus(AK_Base::ActorStatus::ACTION);
			}
#else
			{
				auto scene = new Scene::TestScene(L"TestScene");
				root->AddChild(scene);
				//scene->SetStatus(AK_Base::ActorStatus::ACTION);
			}
			{
				auto scene = new Scene::GameMainScene(L"GameMainScene");
				root->AddChild(scene);
				scene->SetStatus(AK_Base::ActorStatus::ACTION);
			}
#endif
		});
}