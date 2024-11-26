
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// シーンクラス
// 
// 製作者	: amateurK
// 作成日	: 2024/04/22
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Scene.h"

namespace Scene {
	//--------------------------------------------------------------------------------------
	Scene::Scene()
		: Actor()
		, m_Times(0)
	{
		// 基本お休み
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