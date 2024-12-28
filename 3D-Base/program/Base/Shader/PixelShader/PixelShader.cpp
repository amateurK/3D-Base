
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �s�N�Z���V�F�[�_�[�̊��N���X
// 
// 
// �����	: amateurK
// �쐬��	: 2024/12/04
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "PixelShader.h"

namespace Shader {

	PixelShader::PixelShader()
		: ShaderBase()
	{

	}

	//--------------------------------------------------------------------------------------
	PixelShader::~PixelShader()
	{

	}

	//--------------------------------------------------------------------------------------
	HRESULT PixelShader::Init(const ShaderInitParam& params)
	{
		HRESULT hr = S_OK;

		// ���_�V�F�[�_�[��ǂݍ���
		auto blob = DX::ReadData(params.FilePath.c_str());
		// ���_�V�F�[�_�[���쐬
		hr = m_D3DDevice->CreatePixelShader(blob.data(), blob.size(),
			nullptr, m_PixelShader.ReleaseAndGetAddressOf());
		if (FAILED(hr)) {
			blob.clear();
			return hr;
		}

		return hr;
	}

	//--------------------------------------------------------------------------------------
	void PixelShader::SetShader(const ShaderSet* set)
	{
		// �`�揀��
		m_ImmediateContext->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	}

	//--------------------------------------------------------------------------------------
	void PixelShader::UpdateGPUConstantBuffer(size_t index)
	{
		m_ImmediateContext->PSSetConstantBuffers(static_cast<UINT>(index),
			1, m_CBList[index].Buffer.GetAddressOf());

	}

}