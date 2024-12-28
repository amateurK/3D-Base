
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���ʂ̒��_�V�F�[�_�[
// 
// �����	: amateurK
// �쐬��	: 2024/12/08
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "BasicVS.h"
#include "../ShaderManager.h"

namespace Shader {

	BasicVS::BasicVS()
		:VertexShader()
	{

	}
	//--------------------------------------------------------------------------------------
	BasicVS::~BasicVS()
	{

	}

	//--------------------------------------------------------------------------------------
	HRESULT BasicVS::Init(const ShaderInitParam& params)
	{
		HRESULT hr = S_OK;

		hr = __super::Init(params);
		if (FAILED(hr))return hr;

		// �R���X�^���g�o�b�t�@���Z�b�g
		CreateConstantBuffer(sizeof(ChangesFrame));
		CreateConstantBuffer(sizeof(Material));

		return hr;
	}

	//--------------------------------------------------------------------------------------
	void BasicVS::SetPerObject(const ShaderSet* set)
	{
		SetChangeFrame(*(set->GetData<const XMMATRIX*>("worldMatrix")));
		SetConstantBuffer<Material>(1, set->GetData<XMFLOAT4>("color"));
	}

	//--------------------------------------------------------------------------------------
	void BasicVS::AddDataForShaderSet(ShaderSet* set) const
	{
		set->SetData<const XMMATRIX*>("worldMatrix", nullptr);
		set->SetData<XMFLOAT4>("color", {1.0f, 1.0f, 1.0f, 1.0f});
	}

	//--------------------------------------------------------------------------------------
	void BasicVS::SetChangeFrame(const XMMATRIX& world)
	{
		// WVP�s����Z�o
		auto matWVP = ShaderManager::GetInstance()->CalcWVPMatrix(world);

		SetConstantBuffer<ChangesFrame>(0, matWVP);
	}
}
