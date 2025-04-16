
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 直進する弾コンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2025/04/14
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "SimpleBullet.h"
#include "Base/Component/Transform.h"
#include "Base/Input/InputManager.h"

using namespace DirectX;

namespace AK_Game {

	SimpleBullet::SimpleBullet(AK_Base::Actor* const parent)
		: Component(parent)
		, m_Speed(XMVectorZero())
		, m_LifeTime(0.0f)
	{

	}

	//---------------------------------------------------------------------------------------------
	void SimpleBullet::Update(const double& totalTime, const float& elapsedTime)
	{
		auto transform = GetActor()->GetTransform();

		// 反映
		transform->Move(m_Speed * (0.5f * elapsedTime));

		// ライフタイムを減少
		m_LifeTime -= elapsedTime;

		// 消失判定
		if (m_LifeTime <= 0.0f)
		{
			GetActor()->SetStatus(AK_Base::ActorStatus::DEAD);
		}
	}

}