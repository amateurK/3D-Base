
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Փ˔�����s���R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2025/01/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Collider.h"
#include "Transform.h"

using namespace DirectX;

namespace AK_Base {

	//--------------------------------------------------------------------------------------
	Collider::Collider(Actor* const parent)
		: Component(parent)
		, m_Transform(nullptr)
	{
		m_Transform = GetActor()->GetComponent<Transform>();

		auto a = m_Transform->GetName();

		auto b = GetActor()->GetTransform()->GetName();

	}
}