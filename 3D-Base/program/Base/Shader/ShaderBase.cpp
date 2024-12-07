
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 各種シェーダーの基底クラス
// 
// 
// 製作者	: amateurK
// 作成日	: 2024/11/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "ShaderBase.h"
#include "../BaseWindow.h"

namespace Shader {

	/// @brief コンストラクタ
	ShaderBase::ShaderBase()
	{
		auto& game = AK_Base::BaseWindow::GetInstance();
		m_D3DDevice = game.GetD3DDevice();
		m_ImmediateContext = game.GetImmediateContext();
	}

	//--------------------------------------------------------------------------------------
	ShaderBase::~ShaderBase()
	{

	}

	//--------------------------------------------------------------------------------------
	HRESULT ShaderBase::CreateConstantBuffer(UINT size)
	{
		HRESULT hr = S_OK;
		ConstantBuffer cb = { nullptr, size };

		D3D11_BUFFER_DESC bd = {};
		//// UpdateSubresourceを使用する場合はこっち
		//bd.Usage = D3D11_USAGE_DEFAULT;
		//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//bd.CPUAccessFlags = 0;
		// Map, Unmapを使用する場合はこっち
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.ByteWidth = size;
		hr = m_D3DDevice->CreateBuffer(&bd, nullptr, cb.Buffer.ReleaseAndGetAddressOf());
		if (FAILED(hr))return hr;
		m_CBList.push_back(std::move(cb));

		return hr;
	}
}
