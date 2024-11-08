
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert�V�F�[�_�[�N���X
// 
// �����	: amateurK
// �쐬��	: 2024/08/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "LambertShader.h"
#include "../BaseWindow.h"

namespace Shader {


	//--------------------------------------------------------------------------------------
	LambertShader::LambertShader()
		: Shader()
	{
		Create();
	}
	//--------------------------------------------------------------------------------------
	LambertShader::~LambertShader()
	{
		m_ChangesFrame.Reset();
		m_Material.Reset();
		m_Light.Reset();
	}


	//--------------------------------------------------------------------------------------
	void LambertShader::SetRendering()
	{
		m_ImmediateContext->IASetInputLayout(m_VertexLayout.Get());

		// �V�F�[�_�[�E�`��̐ݒ�
		m_ImmediateContext->VSSetShader(m_VertexShader.Get(), nullptr, 0);
		m_ImmediateContext->VSSetConstantBuffers(0, 1, m_ChangesFrame.GetAddressOf());
		m_ImmediateContext->VSSetConstantBuffers(1, 1, m_Material.GetAddressOf());
		m_ImmediateContext->VSSetConstantBuffers(2, 1, m_Light.GetAddressOf());

		m_ImmediateContext->PSSetShader(m_PixelShader.Get(), nullptr, 0);
		m_ImmediateContext->PSSetSamplers(0, 1, m_Sampler.GetAddressOf());
		
	}


	//--------------------------------------------------------------------------------------
	void LambertShader::SetChangesFrame(const XMVECTOR& lightDirection)
	{
		// �s��̌v�Z
		XMMATRIX matWVP = m_World * m_View * m_Projection;
		matWVP = XMMatrixTranspose(matWVP);	// �]�u

		// ���̕����̌v�Z�i���̂̃��[�J�����W�ɕϊ��j
		XMVECTOR vec = {};
		auto matLight = XMMatrixInverse(&vec, m_World);	// �t�s��
		auto light = XMVector4Transform(lightDirection, matLight);	// ���[�J�����W�ɕϊ�
		light = XMVector3Normalize(light);

		// �R���X�^���g�o�b�t�@�̍X�V
		D3D11_MAPPED_SUBRESOURCE subResource = {};
		m_ImmediateContext->Map(m_ChangesFrame.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		auto cb = (ChangesFrame*)subResource.pData;
		cb->MatrixWVP = matWVP;
		cb->LightDirection = light;
		m_ImmediateContext->Unmap(m_ChangesFrame.Get(), 0);

	}

	//--------------------------------------------------------------------------------------
	void LambertShader::SetMaterial(const XMFLOAT4& materialAmbient, const XMFLOAT4& materialDiffuse)
	{

		// �R���X�^���g�o�b�t�@�̍X�V
		D3D11_MAPPED_SUBRESOURCE subResource = {};
		m_ImmediateContext->Map(m_Material.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		auto cb = (Material*)subResource.pData;
		cb->MaterialAmbient = materialAmbient;
		cb->MaterialDiffuse = materialDiffuse;
		m_ImmediateContext->Unmap(m_Material.Get(), 0);

	}

	//--------------------------------------------------------------------------------------
	void LambertShader::SetLight(const XMFLOAT4& lightAmbient, const XMFLOAT4& lightDiffuse)
	{
		// �R���X�^���g�o�b�t�@�̍X�V
		D3D11_MAPPED_SUBRESOURCE subResource = {};
		m_ImmediateContext->Map(m_Light.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		auto cb = (Light*)subResource.pData;
		cb->LightAmbient = lightAmbient;
		cb->LightDiffuse = lightDiffuse;
		m_ImmediateContext->Unmap(m_Light.Get(), 0);

	}


	//--------------------------------------------------------------------------------------
	HRESULT LambertShader::Create() {

		HRESULT hr = S_OK;

		// ���_�V�F�[�_�[��ǂݍ���
		auto vsBlob = DX::ReadData(L"LambertVertexShader.cso");
		// ���_�V�F�[�_�[���쐬
		hr = m_D3DDevice->CreateVertexShader(vsBlob.data(), vsBlob.size(),
			nullptr, m_VertexShader.ReleaseAndGetAddressOf());
		if (FAILED(hr)) {
			vsBlob.clear();
			return hr;
		}

		// Define the input layout
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);
		// Create the input layout
		hr = m_D3DDevice->CreateInputLayout(layout, numElements, vsBlob.data(),
			vsBlob.size(), m_VertexLayout.ReleaseAndGetAddressOf());
		vsBlob.clear();
		if (FAILED(hr))
			return hr;

		// �s�N�Z���V�F�[�_�[��ǂݍ���
		auto psBlob = DX::ReadData(L"LambertPixelShader.cso");
		// �s�N�Z���V�F�[�_�[���쐬
		hr = m_D3DDevice->CreatePixelShader(psBlob.data(), psBlob.size(),
			nullptr, m_PixelShader.ReleaseAndGetAddressOf());
		psBlob.clear();
		if (FAILED(hr)) {
			return hr;
		}

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
		smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		smpDesc.BorderColor[0] = 1.0f;	// ���Address������D3D11_TEXTURE_ADDRESS_BORDER���g�����ꍇ�̐F
		smpDesc.BorderColor[1] = 0.0f;	// #ff00ff��Unity�݂����ɂȂ�
		smpDesc.BorderColor[2] = 1.0f;	// �킩��₷��
		smpDesc.BorderColor[3] = 1.0f;
		m_D3DDevice->CreateSamplerState(&smpDesc, &m_Sampler);
		m_ImmediateContext->PSSetSamplers(0, 1, &m_Sampler);


		// Create the constant buffer
		D3D11_BUFFER_DESC bd = {};
		//// UpdateSubresource���g�p����ꍇ�͂�����
		//bd.Usage = D3D11_USAGE_DEFAULT;
		//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//bd.CPUAccessFlags = 0;
		// Map, Unmap���g�p����ꍇ�͂�����
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.ByteWidth = sizeof(ChangesFrame);
		hr = m_D3DDevice->CreateBuffer(&bd, nullptr, m_ChangesFrame.ReleaseAndGetAddressOf());
		if (FAILED(hr))
			return hr;

		bd.ByteWidth = sizeof(Material);
		hr = m_D3DDevice->CreateBuffer(&bd, nullptr, m_Material.ReleaseAndGetAddressOf());
		if (FAILED(hr))
			return hr;

		bd.ByteWidth = sizeof(Light);
		hr = m_D3DDevice->CreateBuffer(&bd, nullptr, m_Light.ReleaseAndGetAddressOf());
		if (FAILED(hr))
			return hr;

		return hr;
	}
}