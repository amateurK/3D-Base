
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �V�[���N���X
// 
// �����	: amateurK
// �쐬��	: 2024/04/22
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Scene.h"

namespace Scene {
	//--------------------------------------------------------------------------------------
	Scene::Scene()
		: Actor()
		, m_Times(0)
	{
		// ��{���x��
		SetStatus(AK_Base::ActorStatus::REST);
	}

	//--------------------------------------------------------------------------------------
	Scene::~Scene()
	{

	}


	void Scene::Update(const double& totalTime, const float& elapsedTime)
	{
		m_Times++;

		Actor::Update(totalTime, elapsedTime);
	}
}