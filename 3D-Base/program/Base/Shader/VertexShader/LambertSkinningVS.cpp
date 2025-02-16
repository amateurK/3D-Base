
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert頂点シェーダー
// 
// 製作者	: amateurK
// 作成日	: 2024/12/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "LambertSkinningVS.h"
#include "../ShaderManager.h"

using namespace DirectX;

constexpr int BONE_MAX = 100;

namespace Shader {

	LambertSkinningVS::LambertSkinningVS()
		:LambertVS()
	{

	}
	//--------------------------------------------------------------------------------------
	LambertSkinningVS::~LambertSkinningVS()
	{

	}

	//--------------------------------------------------------------------------------------
	HRESULT LambertSkinningVS::Init(const ShaderInitParam& params)
	{
		HRESULT hr = S_OK;

		hr = __super::Init(params);
		if (FAILED(hr))return hr;

		CreateConstantBuffer(sizeof(DirectX::XMMATRIX) * BONE_MAX);

		return hr;
	}

	//--------------------------------------------------------------------------------------
	void LambertSkinningVS::SetShader(const ShaderSet* set)
	{
		__super::SetShader(set);

	}

	//--------------------------------------------------------------------------------------
	void LambertSkinningVS::SetPerObject(const ShaderSet* set)
	{
		__super::SetPerObject(set);

		auto bones = set->GetData<const std::vector<DirectX::XMMATRIX>*>("BoneMatrices");
#ifdef _DEBUG
		if (bones->size() > BONE_MAX)
		{
			throw std::exception("BoneMatrices size is over BONE_MAX");
		}
#endif // DEBUG

		SetConstantBufferWithArray<XMMATRIX>(3, bones->data(), bones->size());
	}

	//--------------------------------------------------------------------------------------
	void LambertSkinningVS::AddDataForShaderSet(ShaderSet* set) const
	{
		__super::AddDataForShaderSet(set);
		// 先に場所を作成
		set->SetData<const std::vector<DirectX::XMMATRIX>*>("BoneMatrices", nullptr);
	}
}
