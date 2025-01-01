
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert頂点シェーダー
// 
// 製作者	: amateurK
// 作成日	: 2024/12/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "LambertVS.h"
#include "../ShaderManager.h"

using namespace DirectX;

namespace Shader {

	LambertVS::LambertVS()
		:VertexShader()
	{

	}
	//--------------------------------------------------------------------------------------
	LambertVS::~LambertVS()
	{

	}

	//--------------------------------------------------------------------------------------
	HRESULT LambertVS::Init(const ShaderInitParam& params)
	{
		HRESULT hr = S_OK;

		hr = __super::Init(params);
		if (FAILED(hr))return hr;

		// コンスタントバッファをセット
		CreateConstantBuffer(sizeof(ChangesFrame));
		CreateConstantBuffer(sizeof(Material));
		CreateConstantBuffer(sizeof(Light));

		return hr;
	}

	//--------------------------------------------------------------------------------------
	void LambertVS::SetShader(const ShaderSet* set)
	{
		__super::SetShader(set);


		SetConstantBuffer<Material>(1, set->GetData<XMFLOAT4>("materialAmbient"), set->GetData<XMFLOAT4>("materialDiffuse"));
		SetConstantBuffer<Light>(2, set->GetData<XMFLOAT4>("lightAmbient"), set->GetData<XMFLOAT4>("lightDiffuse"));
	}

	//--------------------------------------------------------------------------------------
	void LambertVS::SetPerObject(const ShaderSet* set)
	{
		SetChangeFrame(*(set->GetData<const XMMATRIX*>("worldMatrix")), set->GetData<XMVECTOR>("lightDirection"));
	}

	//--------------------------------------------------------------------------------------
	void LambertVS::AddDataForShaderSet(ShaderSet* set) const
	{
		// 先に場所を作成
		set->SetData<XMFLOAT4>("materialAmbient", {1.0f, 1.0f, 1.0f, 1.0f});
		set->SetData<XMFLOAT4>("materialDiffuse", { 1.0f, 1.0f, 1.0f, 1.0f });
		set->SetData<XMFLOAT4>("lightAmbient", { 0.1f, 0.1f, 0.1f, 1.0f });
		set->SetData<XMFLOAT4>("lightDiffuse", { 1.0f, 1.0f, 1.0f, 1.0f });
		set->SetData<const XMMATRIX*>("worldMatrix", nullptr);
		set->SetData<XMVECTOR>("lightDirection", XMVectorSet( 0.0f, 0.0f, 1.0f, 1.0f ));
	}

	//--------------------------------------------------------------------------------------
	void LambertVS::SetChangeFrame(const XMMATRIX& world, const XMVECTOR& light)
	{
		// WVP行列を算出
		auto matWVP = ShaderManager::GetInstance()->CalcWVPMatrix(world);

		// 光の向きをローカル座標に変換
		auto worldInv = XMMatrixInverse(nullptr, world);
		auto vecLight = XMVector4Transform(light, worldInv);	// ローカル座標に変換
		vecLight = XMVector3Normalize(vecLight);

		SetConstantBuffer<ChangesFrame>(0, matWVP, vecLight);
	}
}
