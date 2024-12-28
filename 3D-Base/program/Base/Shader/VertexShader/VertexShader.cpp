
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���_�V�F�[�_�[�̊��N���X
// 
// 
// �����	: amateurK
// �쐬��	: 2024/11/30
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

		// ���_�V�F�[�_�[��ǂݍ���
		auto vsBlob = DX::ReadData(param.FilePath.c_str());
		// ���_�V�F�[�_�[���쐬
		hr = m_D3DDevice->CreateVertexShader(vsBlob.data(), vsBlob.size(),
			nullptr, m_VertexShader.ReleaseAndGetAddressOf());
		if (FAILED(hr)) {
			vsBlob.clear();
			return hr;
		}

		// ���̓��C�A�E�g�̍쐬
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
		// �`�揀��
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