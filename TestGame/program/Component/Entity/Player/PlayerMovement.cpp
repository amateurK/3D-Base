
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �v���C���[�̈ړ��𐧌䂷��R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2025/01/07
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "PlayerMovement.h"
#include "Base/Component/Transform.h"
#include "Base/Input/InputManager.h"

using namespace DirectX;

namespace AK_Game {

	PlayerMovement::PlayerMovement(AK_Base::Actor* const parent)
		: Component(parent)
		, m_Speed(XMVectorZero())
		, m_AirResistance(0.0f) //{ 0.1f, 0.1f, 0.1f, 0.0f }
		, m_NormalAccel(XMVectorZero()) //{ 10.0f, 5.0f, 10.0f, 0.0f }
	{

	}

	//---------------------------------------------------------------------------------------------
	void PlayerMovement::Update(const double& totalTime, const float& elapsedTime)
	{
		auto transform = GetActor()->GetTransform();
		auto input = AK_Base::InputManager::GetInstance();

		// �ړ��ʂ��擾
		bool w = input->IsKeyPressed(DIK_W);
		bool s = input->IsKeyPressed(DIK_S);
		bool a = input->IsKeyPressed(DIK_A);
		bool d = input->IsKeyPressed(DIK_D);
		bool z = input->IsKeyPressed(DIK_Z);
		bool x = input->IsKeyPressed(DIK_X);
		XMVECTOR moveVec = XMVector3Normalize( XMVectorSet(
			(float)(d - a),	// right
			(float)(z - x),	// up
			(float)(w - s),	// front
			0.0f
		));

		// �v�Z�O�̑��x��ۑ�
		auto preSpeed = m_Speed;

		// �ړ����͂ɂ�������ǉ�
		m_Speed += m_NormalAccel * moveVec * elapsedTime;
		// ��C��R����Z
		//m_Speed *= XMVectorPow(m_AirResistance, XMVectorSet(elapsedTime, elapsedTime, elapsedTime, 0.0f));
		//m_Speed *= 1.0 - (1.0f - m_AirResistance) * elapsedTime;
		m_Speed *= powf(m_AirResistance, elapsedTime);


		transform->Move((preSpeed + m_Speed) * (0.5f * elapsedTime));
	}

}