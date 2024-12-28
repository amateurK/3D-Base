
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 頂点シェーダーの基底クラス
// 
// 
// 製作者	: amateurK
// 作成日	: 2024/11/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "VertexShader.h"

namespace Shader {

	VertexShader::VertexShader()
		: ShaderBase()
	{

	}

	//--------------------------------------------------------------------------------------
	VertexShader::~VertexShader()
	{

	}

	//--------------------------------------------------------------------------------------
	HRESULT VertexShader::Init(const ShaderInitParam& params)
	{
		const auto& param = static_cast<const VertexShaderInitParam&>(params);
		HRESULT hr = S_OK;

		// 頂点シェーダーを読み込み
		auto vsBlob = DX::ReadData(param.FilePath.c_str());
		// 頂点シェーダーを作成
		hr = m_D3DDevice->CreateVertexShader(vsBlob.data(), vsBlob.size(),
			nullptr, m_VertexShader.ReleaseAndGetAddressOf());
		if (FAILED(hr)) {
			vsBlob.clear();
			return hr;
		}

		// 入力レイアウトの作成
		hr = m_D3DDevice->CreateInputLayout(param.Layout, param.LayoutCount, vsBlob.data(),
			vsBlob.size(), m_InputLayout.ReleaseAndGetAddressOf());
		vsBlob.clear();
		if (FAILED(hr))
			return hr;

		return hr;
	}

	//--------------------------------------------------------------------------------------
	void VertexShader::SetShader(const ShaderSet* set)
	{
		// 描画準備
		m_ImmediateContext->VSSetShader(m_VertexShader.Get(), nullptr, 0);
		m_ImmediateContext->IASetInputLayout(m_InputLayout.Get());
	}

	//--------------------------------------------------------------------------------------
	void VertexShader::UpdateGPUConstantBuffer(size_t index)
	{
		m_ImmediateContext->VSSetConstantBuffers(static_cast<UINT>(index),
			1, m_CBList[index].Buffer.GetAddressOf());

	}

}