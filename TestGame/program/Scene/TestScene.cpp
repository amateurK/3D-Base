
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �e�X�g�p�N���X
// 
// �����	: amateurK
// �쐬��	: 2024/04/22
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "TestScene.h"
#include "Base/Model/ModelActor.h"
#include "../Piece/Piece.h"
#include "Base/Input/InputManager.h"

namespace Scene {

	TestScene::TestScene()
		: Scene()
	{
		this->SetStatus(AK_Base::ActorStatus::ACTION);
		auto myGame(&AK_Base::BaseWindow::GetInstance());

		//auto testobj = new AK_Base::ModelActor(Game->GetBasicShader());
		//Game->GetRootActor()->AddChild(testobj);

		//auto piece1 = new Piece::Piece(myGame->GetTestShader(), L"no.1", L"resource/testData/Alicia_FBX/Alicia_solid_Unity.FBX");
		//this->AddChild(piece1);
		//piece1->SetPosition(-3.0f, 0.0f, 3.0f);
		//piece1->Scaling(0.05f);

		auto piece2 = new Piece::Piece(myGame->GetTestShader(), L"no.2", L"resource/testData/AvatarSample_A.vrm");
		this->AddChild(piece2);
		piece2->SetPosition(3.0f, 0.0f, 3.0f);
		piece2->Scaling(6.0f);


		// �J�����̏���
		m_Camera = std::make_unique<Camera::Camera>();

		//const XMVECTOR eye = { 0.0f, 1.0f, -5.0f, 0.0f };
		//const XMVECTOR at = { 0.0f, 1.0f, 0.0f, 0.0f };
		const XMVECTOR eye = { 0.0f, 4.0f, -2.0f, 0.0f };
		const XMVECTOR at = { 0.0f, 4.0f, 3.0f, 0.0f };
		const XMVECTOR up = { 0.0f, 1.0f, 0.0f, 0.0f };
		m_Camera->SetCamera(&eye, &at, &up);

		auto windowSize = myGame->GetWindowSize();
		m_Camera->SetScreen(XM_PIDIV2, static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y));

		// �V�F�[�_�[�ɃZ�b�g
		auto shader = myGame->GetTestShader();
		shader->SetViewMatrix(m_Camera->GetView());
		shader->SetProjectionMatrix(m_Camera->GetProjection());
	}
	//--------------------------------------------------------------------------------------
	TestScene::~TestScene()
	{

	}

	//--------------------------------------------------------------------------------------
	void TestScene::Move(const double& totalTime, const float& elapsedTime)
	{
		// �J������]�e�X�g
		{
			//// �L�[���͂̌��m
			//bool w = (GetAsyncKeyState('W') & 0x8000) == 0x8000;
			//bool s = (GetAsyncKeyState('S') & 0x8000) == 0x8000;
			//bool a = (GetAsyncKeyState('A') & 0x8000) == 0x8000;
			//bool d = (GetAsyncKeyState('D') & 0x8000) == 0x8000;
			//bool z = (GetAsyncKeyState('Z') & 0x8000) == 0x8000;
			//bool x = (GetAsyncKeyState('X') & 0x8000) == 0x8000;

			auto input = AK_Base::InputManager::GetInstance();
			bool w = input->IsKeyPressed('W');
			bool s = input->IsKeyPressed('S');
			bool a = input->IsKeyPressed('A');
			bool d = input->IsKeyPressed('D');
			bool z = input->IsKeyPressed('Z');
			bool x = input->IsKeyPressed('X');


			// �J�����̎��^�]
			float speed = 2.0f * elapsedTime;
			float front = (float)(w - s) * speed;
			float right = (float)(d - a) * speed;
			float up = (float)(z - x) * speed;
			m_Camera->MoveWithViewpoint(front, right, up);
		}


		// �V�F�[�_�[��view�s�������
		auto myGame(&AK_Base::BaseWindow::GetInstance());
		auto shader = myGame->GetTestShader();
		shader->SetViewMatrix(m_Camera->GetView());

		Scene::Move(totalTime, elapsedTime);
	}


}