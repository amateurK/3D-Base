
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert頂点シェーダー
// 
// 製作者	: amateurK
// 作成日	: 2024/12/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "LambertVS.h"
#include "../ShaderManager.h"

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
	void LambertVS::SetChangeFrame(const XMMATRIX& world, const XMVECTOR& light)
	{
		// WVP行列を算出
		auto matWVP = world * *(ShaderManager::GetInstance()->GetVPMatrix());
		matWVP = XMMatrixTranspose(matWVP);

		// 光の向きをローカル座標に変換
		auto worldInv = XMMatrixInverse(nullptr, world);
		auto vecLight = XMVector4Transform(light, worldInv);	// ローカル座標に変換
		vecLight = XMVector3Normalize(light);

		SetConstantBuffer<ChangesFrame>(0, matWVP, vecLight);
	}
}
