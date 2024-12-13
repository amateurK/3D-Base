
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 普通の頂点シェーダー
// 
// 製作者	: amateurK
// 作成日	: 2024/12/08
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

		// コンスタントバッファをセット
		CreateConstantBuffer(sizeof(ChangesFrame));
		CreateConstantBuffer(sizeof(Material));

		return hr;
	}

	//--------------------------------------------------------------------------------------
	void BasicVS::SetChangeFrame(const XMMATRIX& world)
	{
		// WVP行列を算出
		auto matWVP = ShaderManager::GetInstance()->CalcWVPMatrix(world);

		SetConstantBuffer<ChangesFrame>(0, matWVP);
	}
}
