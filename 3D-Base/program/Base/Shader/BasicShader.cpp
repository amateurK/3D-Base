
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �A�Ȃǂ��Ȃ���{�I�ȃV�F�[�_�[
// 
// �����	: amateurK
// �쐬��	: 2024/04/21
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "BasicShader.h"
#include "../BaseWindow.h"

namespace Shader {


	//--------------------------------------------------------------------------------------
	BasicShader::BasicShader()
		: Shader()
	{
		Create();
	}
	//--------------------------------------------------------------------------------------
	BasicShader::~BasicShader()
	{
		m_ChangesFrame.Reset();
	}


	//--------------------------------------------------------------------------------------
	void BasicShader::SetRendering()
	{
		// �s��̌v�Z
		DirectX::XMMATRIX matWVP = m_World * m_View * m_Projection;

		// �s��̍X�V
		ChangesFrame cb = {};
		cb.matrixWVP = DirectX::XMMatrixTranspose(matWVP);
		m_ImmediateContext->UpdateSubresource(m_ChangesFrame.Get(), 0, nullptr, &cb, 0, 0);


		// �V�F�[�_�[�E�`��̐ݒ�
		m_ImmediateContext->VSSetShader(m_VertexShader.Get(), nullptr, 0);
		m_ImmediateContext->IASetInputLayout(m_VertexLayout.Get());
		m_ImmediateContext->VSSetConstantBuffers(0, 1, m_ChangesFrame.GetAddressOf());

		m_ImmediateContext->PSSetShader(m_PixelShader.Get(), nullptr, 0);
		m_ImmediateContext->PSSetSamplers(0, 1, m_Sampler.GetAddressOf());

		FLOAT BlendFactor[4] = { 0.0f };
		m_ImmediateContext->OMSetBlendState(m_BlendState.Get(), BlendFactor, 0xFFFFFFFF);
	}

	//--------------------------------------------------------------------------------------
	HRESULT BasicShader::Create() {

		HRESULT hr = S_OK;

		// Compile the vertex shader
		ID3DBlob* vsBlob = nullptr;
		hr = CompileShaderFromFile(L"program/Base/Shader/BasicShader.hlsli", "VS", "vs_4_0", &vsBlob);
		if (FAILED(hr)) {
			MessageBox(nullptr,
				L"The HLSL file cannot be Vertex shader compiled.", L"Error", MB_OK);
			return hr;
		}
		// Create the vertex shader
		hr = m_D3DDevice->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
			nullptr, m_VertexShader.ReleaseAndGetAddressOf());
		if (FAILED(hr)) {
			vsBlob->Release();
			return hr;
		}

		// Define the input layout
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);
		// Create the input layout
		hr = m_D3DDevice->CreateInputLayout(layout, numElements, vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(), m_VertexLayout.ReleaseAndGetAddressOf());
		vsBlob->Release();
		if (FAILED(hr))
			return hr;

		// Compile the pixel shader
		ID3DBlob* psBlob = nullptr;
		hr = CompileShaderFromFile(L"program/Base/Shader/BasicShader.hlsli", "PS", "ps_4_0", &psBlob);
		if (FAILED(hr)) {
			MessageBox(nullptr,
				L"The HLSL file cannot be Pixel shader compiled", L"Error", MB_OK);
			return hr;
		}
		// Create the pixel shader
		hr = m_D3DDevice->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(),
			nullptr, m_PixelShader.ReleaseAndGetAddressOf());
		psBlob->Release();
		if (FAILED(hr))
			return hr;

		//�u�����h�X�e�[�g�̐ݒ�
		D3D11_BLEND_DESC bld = {};
		bld.AlphaToCoverageEnable = FALSE;
		bld.IndependentBlendEnable = FALSE;
		bld.RenderTarget[0].BlendEnable = TRUE;
		bld.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bld.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bld.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bld.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bld.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bld.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bld.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_D3DDevice->CreateBlendState(&bld, m_BlendState.ReleaseAndGetAddressOf());
		float fBlendFactor[] = { 0, 0, 0, 0 };

		m_ImmediateContext->OMSetBlendState(m_BlendState.Get(), fBlendFactor, 0xffffffff);


		// �T���v���[�̃Z�b�g
		D3D11_SAMPLER_DESC smpDesc;

		::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
		smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;	// �h�b�g�����ꂢ�ɕ\���i���`��ԂȂ��j
		smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		smpDesc.BorderColor[0] = 1.0f;	// ���Address������D3D11_TEXTURE_ADDRESS_BORDER���g�����ꍇ�̐F
		smpDesc.BorderColor[1] = 0.0f;	// #ff00ff��Unity�݂����ɂȂ�
		smpDesc.BorderColor[2] = 1.0f;	// �킩��₷��
		smpDesc.BorderColor[3] = 1.0f;
		m_D3DDevice->CreateSamplerState(&smpDesc, &m_Sampler);
		m_ImmediateContext->PSSetSamplers(0, 1, &m_Sampler);

		// Create the constant buffer
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.ByteWidth = sizeof(ChangesFrame);
		hr = m_D3DDevice->CreateBuffer(&bd, nullptr, m_ChangesFrame.ReleaseAndGetAddressOf());
		if (FAILED(hr))
			return hr;

		return hr;
	}
}