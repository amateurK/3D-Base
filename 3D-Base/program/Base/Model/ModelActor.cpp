
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 3Dモデルを持ったオブジェクトが継承するクラス
// 
// 製作者	: amateurK
// 作成日	: 2024/04/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "ModelActor.h"
#include "ModelRender.h"

namespace AK_Base {

	//--------------------------------------------------------------------------------------
	ModelActor::ModelActor(
		Shader::Shader* const shader,
		std::wstring name,
		std::wstring fileName
	)
		: Actor(name)
		, m_WorldMatrix(DirectX::XMMatrixIdentity())
		, m_Position(0.0f,0.0f,0.0f)
		, m_Rotation(0.0f)
		, m_IsVisible(true)
	{
		m_ModelRender = std::make_unique<ModelRender>(shader);
		m_ModelRender->CreateResource(fileName);
	}

	//--------------------------------------------------------------------------------------
	ModelActor::~ModelActor()
	{

	}

	//--------------------------------------------------------------------------------------
	void ModelActor::Move(const double& totalTime, const float& elapsedTime)
	{
		//m_Rotation += 0.0001f;
		CalcWorldMatrix();

		Actor::Move(totalTime, elapsedTime);
	}

	//--------------------------------------------------------------------------------------
	void ModelActor::Render(const double& totalTime, const float& elapsedTime)
	{

		m_ModelRender->Render(m_WorldMatrix);

		Actor::Render(totalTime, elapsedTime);
	}

	//--------------------------------------------------------------------------------------
	void ModelActor::CalcWorldMatrix()
	{
		m_WorldMatrix = DirectX::XMMatrixIdentity();
		m_WorldMatrix *= DirectX::XMMatrixRotationY(m_Rotation);
		m_WorldMatrix *= DirectX::XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	}
}