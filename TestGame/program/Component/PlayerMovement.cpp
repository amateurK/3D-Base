
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// プレイヤーの移動を制御するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2025/01/07
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "PlayerMovement.h"
#include "Base/Component/Transform.h"
#include "Base/Input/InputManager.h"

using namespace DirectX;

namespace AK_Game {

	PlayerMovement::PlayerMovement(AK_Base::Actor* const parent)
		: Component(parent)
		, m_Speed(XMVectorZero())
		, m_AirResistance(XMVectorZero()) //{ 0.1f, 0.1f, 0.1f, 0.0f }
		, m_NormalAccel(XMVectorZero()) //{ 10.0f, 5.0f, 10.0f, 0.0f }
	{

	}

	//---------------------------------------------------------------------------------------------
	void PlayerMovement::Update(const double& totalTime, const float& elapsedTime)
	{
		auto transform = GetActor()->GetTransform();
		auto input = AK_Base::InputManager::GetInstance();

		// 移動量を取得
		bool w = input->IsKeyPressed(DIK_W);
		bool s = input->IsKeyPressed(DIK_S);
		bool a = input->IsKeyPressed(DIK_A);
		bool d = input->IsKeyPressed(DIK_D);
		bool z = input->IsKeyPressed(DIK_Z);
		bool x = input->IsKeyPressed(DIK_X);
		XMVECTOR moveVec = XMVector3Normalize( XMVectorSet(
			(float)(w - s),	// front
			(float)(d - a),	// right
			(float)(z - x),	// up
			0.0f
		)); // normalizeがあっているかの検証から

		// 計算前の速度を保存
		auto preSpeed = m_Speed;

		// 移動入力による加速を追加
		m_Speed = (m_Speed + m_NormalAccel * moveVec * elapsedTime)
			// 空気抵抗を乗算
			* XMVectorPow(m_AirResistance, XMVectorSet(elapsedTime, elapsedTime, elapsedTime, 0.0f));



		transform->Move((preSpeed + m_Speed) * (0.5f * elapsedTime));
		//transform->Translate(0.0f, 1.0f * elapsedTime, 0.0f);
	}

}