
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���i����e�R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2025/04/14
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

		// ���f
		transform->Move(m_Speed * (0.5f * elapsedTime));

		// ���C�t�^�C��������
		m_LifeTime -= elapsedTime;

		// ��������
		if (m_LifeTime <= 0.0f)
		{
			GetActor()->SetStatus(AK_Base::ActorStatus::DEAD);
		}
	}

}