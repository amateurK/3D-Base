//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// デバイスやスワップチェインなどを作成するクラス
// ゲームループやウィンドウへの処理もここ
// 
// 製作者	: amateurK
// 作成日	: 2024/03/06
// 2D-Baseから移植したので元の作成日は不明
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "BaseWindow.h"
#include "Actor.h"
#include "Model/Mesh/MeshManager.h"
#include "Input/InputManager.h"
#include "Shader/ShaderManager.h"
#include "Shader/VertexShader/LambertVS.h"
#include "Shader/VertexShader/BasicVS.h"
#include "Shader/PixelShader/PixelShader.h"

namespace AK_Base {
	//--------------------------------------------------------------------------------------
	BaseWindow::BaseWindow()
		: m_WindowSize(0, 0)
		, m_Vsync(1)
	{
		m_RootActor = new AK_Base::Actor(L"RootActor");
	}

	//--------------------------------------------------------------------------------------
	BaseWindow::~BaseWindow()
	{
		if (m_RootActor)delete m_RootActor;
		this->CleanupManager();
		this->CleanupDevice();
	}

	//--------------------------------------------------------------------------------------
	HRESULT BaseWindow::InitWindow(HINSTANCE hInstance, int nCmdShow)
	{
		// ウィンドウクラスを登録
		WNDCLASSEX wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = NULL;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = L"MainWindowClass";
		wcex.hIconSm = NULL;// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
		if (!RegisterClassEx(&wcex))
			return E_FAIL;

		// ウィンドウを作成
		m_HInst = hInstance;
		// 画面サイズ
		// 1280x720(HD) か 1920x1080(Full-HD) に合わせたらいいのかなぁ
		RECT rc = { 0, 0, m_WindowSize.x, m_WindowSize.y };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		m_HWnd = CreateWindowEx(
			0,
			L"MainWindowClass",
			L"Title is here.",
			WS_OVERLAPPEDWINDOW
			^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,// ウィンドウサイズ変更を阻止
			CW_USEDEFAULT,// ウィンドウ左上の画面上の位置
			CW_USEDEFAULT,
			rc.right - rc.left,// ウィンドウサイズ
			rc.bottom - rc.top,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);
		if (!m_HWnd)
			return E_FAIL;

		// ウィンドウ表示
		ShowWindow(m_HWnd, nCmdShow);

		return S_OK;
	}

	//--------------------------------------------------------------------------------------
	HRESULT BaseWindow::InitDevice()
	{
		HRESULT hr = S_OK;
		RECT rc = {};
		GetClientRect(m_HWnd, &rc);
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;

		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};
		UINT numDriverTypes = ARRAYSIZE(driverTypes);

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_12_1,
			D3D_FEATURE_LEVEL_12_0,
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 3;
		sd.OutputWindow = m_HWnd;
		sd.Windowed = TRUE;	// フルスクリーンにするならSetFullscreenState()とかを使おう
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
			m_DriverType = driverTypes[driverTypeIndex];
			hr = D3D11CreateDeviceAndSwapChain(
				nullptr,
				m_DriverType,
				nullptr,
				createDeviceFlags,
				featureLevels,
				numFeatureLevels,
				D3D11_SDK_VERSION,
				&sd,
				&m_SwapChain,
				&m_D3DDevice,
				&m_FeatureLevel,
				&m_ImmediateContext
			);
			if (SUCCEEDED(hr))
				break;
		}
		if (FAILED(hr))
			return hr;

#ifdef _DEBUG
		// デバッグ用デバイスの作成
		hr = m_D3DDevice->QueryInterface(
			__uuidof(ID3D11Debug),
			reinterpret_cast<void**>(&m_D3DDebug)
		);
		if (FAILED(hr))return hr;
#endif


		// Create a render target view
		ID3D11Texture2D* backBuffer = nullptr;
		hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
		if (FAILED(hr))
			return hr;

		hr = m_D3DDevice->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTargetView);
		backBuffer->Release();
		if (FAILED(hr))
			return hr;

		// Create a rasterizer state object that tells the rasterizer stage how to behave
		D3D11_RASTERIZER_DESC rasterizerState = {};
		rasterizerState.FillMode = D3D11_FILL_SOLID;
		rasterizerState.CullMode = D3D11_CULL_BACK;
		//rasterizerState.FillMode = D3D11_FILL_WIREFRAME;
		//rasterizerState.CullMode = D3D11_CULL_NONE;
		rasterizerState.FrontCounterClockwise = false;
		rasterizerState.DepthBias = false;
		rasterizerState.DepthBiasClamp = 0;
		rasterizerState.SlopeScaledDepthBias = 0;
		rasterizerState.DepthClipEnable = true;
		rasterizerState.ScissorEnable = false;
		rasterizerState.MultisampleEnable = false;
		rasterizerState.AntialiasedLineEnable = false;
		m_D3DDevice->CreateRasterizerState(&rasterizerState, &m_RasterStates);
		// Set the rasterizer state
		m_ImmediateContext->RSSetState(m_RasterStates);

		// Create depth stencil texture
		D3D11_TEXTURE2D_DESC descDepth = {};
		descDepth.Width = width;
		descDepth.Height = height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		hr = m_D3DDevice->CreateTexture2D(&descDepth, nullptr, &m_DepthStencil);
		if (FAILED(hr))
			return hr;

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		hr = m_D3DDevice->CreateDepthStencilView(m_DepthStencil, &descDSV, &m_DepthStencilView);
		if (FAILED(hr))
			return hr;

		m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

		//ブレンドステートの設定
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
		m_D3DDevice->CreateBlendState(&bld, &m_BlendState);
		float fBlendFactor[] = { 0, 0, 0, 0 };

		m_ImmediateContext->OMSetBlendState(m_BlendState, fBlendFactor, 0xffffffff);


		// サンプラーのセット
		D3D11_SAMPLER_DESC smpDesc;

		::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
		smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;	// ドットをきれいに表示（線形補間なし）
		smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		smpDesc.BorderColor[0] = 1.0f;	// 上のAddress部分でD3D11_TEXTURE_ADDRESS_BORDERを使った場合の色
		smpDesc.BorderColor[1] = 0.0f;	// #ff00ffでUnityみたいになる
		smpDesc.BorderColor[2] = 1.0f;	// わかりやすい
		smpDesc.BorderColor[3] = 1.0f;
		m_D3DDevice->CreateSamplerState(&smpDesc, &m_Sampler);
		m_ImmediateContext->PSSetSamplers(0, 1, &m_Sampler);

		// Setup the viewport
		D3D11_VIEWPORT vp = {};
		vp.Width = static_cast<FLOAT>(width);
		vp.Height = static_cast<FLOAT>(height);
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_ImmediateContext->RSSetViewports(1, &vp);

		// Set primitive topology
		m_ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// フレームレートの設定
		SetFrameRate(60);

		return S_OK;
	}


	//--------------------------------------------------------------------------------------
	void BaseWindow::CreateManager()
	{

		// メッシュマネージャーの生成
		Mesh::MeshManager::Create();
		InputManager::Create();

		// シェーダーの作成
		Shader::ShaderManager::Create();
		auto shaderM = Shader::ShaderManager::GetInstance();

		{
			// LambertVS
			Shader::VertexShaderInitParam VSparam = {};
			VSparam.FilePath = L"LambertVertexShader.cso";
			D3D11_INPUT_ELEMENT_DESC layout[] = { // TODO 一気に入れれない？
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			VSparam.Layout = layout;
			VSparam.LayoutCount = ARRAYSIZE(layout);
			shaderM->AddShader<Shader::LambertVS>("LambertVS", VSparam);
			// LambertPS
			shaderM->AddShader<Shader::PixelShader>("LambertPS", { L"LambertPixelShader.cso" });
		}
		{
			// LambertShader
			std::unordered_map<Shader::ShaderType, std::string> list;
			list[Shader::ShaderType::VertexShader] = "LambertVS";
			list[Shader::ShaderType::PixelShader] = "LambertPS";
			shaderM->AddShaderSet("LambertShader", list);
		}

		{
			// BasicVS
			Shader::VertexShaderInitParam VSparam = {};
			VSparam.FilePath = L"BasicVertexShader.cso";
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			VSparam.Layout = layout;
			VSparam.LayoutCount = ARRAYSIZE(layout);
			shaderM->AddShader<Shader::BasicVS>("BasicVS", VSparam);
			// BasicPS
			shaderM->AddShader<Shader::PixelShader>("BasicPS", { L"BasicPixelShader.cso" });
		}
		{
			// BasicShader
			std::unordered_map<Shader::ShaderType, std::string> list;
			list[Shader::ShaderType::VertexShader] = "BasicVS";
			list[Shader::ShaderType::PixelShader] = "BasicPS";
			shaderM->AddShaderSet("BasicShader", list);
		}
	}

	//--------------------------------------------------------------------------------------
	void BaseWindow::CleanupManager()
	{
		// マネージャーの破棄
		Mesh::MeshManager::Destroy();
		InputManager::Destroy();

		Shader::ShaderManager::Destroy();
	}

	//--------------------------------------------------------------------------------------
	void BaseWindow::CleanupDevice()
	{
		if (m_ImmediateContext) m_ImmediateContext->ClearState();

		if (m_Sampler)m_Sampler->Release();
		if (m_BlendState)m_BlendState->Release();
		if (m_DepthStencilView)m_DepthStencilView->Release();
		if (m_DepthStencil)m_DepthStencil->Release();
		if (m_RasterStates) m_RasterStates->Release();
		if (m_RenderTargetView) m_RenderTargetView->Release();
		if (m_SwapChain) m_SwapChain->Release();
		if (m_ImmediateContext) m_ImmediateContext->Release();
		if (m_D3DDevice) m_D3DDevice->Release();

#ifdef _DEBUG
		m_D3DDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);

		if (m_D3DDebug) m_D3DDebug->Release();
#endif
	}

	//--------------------------------------------------------------------------------------
	void BaseWindow::GameLoop()
	{


		m_StepTimer.Tick([&]()
			{
				// Managerを動かす
				InputManager::GetInstance()->Update();

				auto time = static_cast<double>(m_StepTimer.GetTotalSeconds());
				auto elapsedTime = static_cast<float>(m_StepTimer.GetElapsedSeconds());
				m_RootActor->Update(time, elapsedTime);
				m_RootActor->CheckStatus();

				// 背景塗りつぶし
				//m_ImmediateContext->ClearRenderTargetView(m_RenderTargetView, DirectX::Colors::LightSeaGreen);
				m_ImmediateContext->ClearRenderTargetView(m_RenderTargetView, DirectX::Colors::Black);
				m_ImmediateContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
				m_RootActor->Render(time, elapsedTime);
			});

		m_SwapChain->Present((UINT)m_Vsync, 0);

	}

	//---------------------------------------------------------------------------------------------
	void BaseWindow::SetFrameRate(int16_t num)
	{
		switch (num)
		{
		case -1:	// 垂直同期
			m_StepTimer.SetFixedTimeStep(false);
			m_Vsync = 1;
			break;
		case 0:		// 無制限
			m_StepTimer.SetFixedTimeStep(false);
			m_Vsync = 0;
			break;
		default:	// 固定
			m_StepTimer.SetFixedTimeStep(true);
			m_StepTimer.SetTargetElapsedSeconds(1.0 / static_cast<double>(num));
			m_Vsync = 0;
			break;
		}
	}

	//--------------------------------------------------------------------------------------
	void BaseWindow::SetWindowSize(const Point<int>& size)
	{
		m_WindowSize = size;
	}

	//--------------------------------------------------------------------------------------
	const Point<int> BaseWindow::GetWindowSize()
	{
		return m_WindowSize;
	}
}