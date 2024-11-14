
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 3Dモデル描画管理クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/04/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "ModelRender.h"
#include "../BaseWindow.h"
#include "Mesh/MeshManager.h"
#include "../Shader/LambertShader.h"

namespace AK_Base {
	//--------------------------------------------------------------------------------------
	ModelRender::ModelRender(Shader::Shader* const shader)
		: m_Shader(shader)
		, m_Mesh(nullptr)
	{

	}

	//--------------------------------------------------------------------------------------
	ModelRender::~ModelRender()
	{
		m_Shader = nullptr;
		m_Mesh = nullptr;

	}

	//--------------------------------------------------------------------------------------
	HRESULT ModelRender::CreateResource(std::wstring fileName)
	{
		HRESULT hr = S_OK;

		hr = Mesh::MeshManager::GetInstance()->
			CreateMesh(fileName, m_Mesh);
		if (FAILED(hr))
			return hr;

		return hr;
	}

	//--------------------------------------------------------------------------------------
	void ModelRender::Render(const DirectX::XMMATRIX& worldMatrix)
	{

		BaseWindow& bw(BaseWindow::GetInstance());
		ID3D11DeviceContext* d3dDeviceContext = bw.GetImmediateContext();

		//// テスト
		//static float _rad = 0.0f;
		//_rad += 0.0001f;
		//float z = std::sin(_rad);

		XMVECTOR lightDirection = { 0.0f, 0.0f, 3.0f, 1.0f };
		XMFLOAT4 lightAmbient = {0.1f, 0.1f, 0.1f, 1.0f};
		XMFLOAT4 lightDiffuse = {1.0f, 1.0f, 1.0f, 1.0f};
		XMFLOAT4 materialAmbient = { 1.0f, 1.0f, 1.0f, 1.0f };
		XMFLOAT4 materialDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f };

		m_Mesh->Render(d3dDeviceContext, [&](int id, const std::vector<Mesh::MeshData> material)
			{
				auto shader = (Shader::LambertShader*)(m_Shader);
				shader->SetWorldMatrix(worldMatrix);
				//shader->SetWorldMatrix(worldMatrix * DirectX::XMMatrixTranslation(0.0f, 0.0f, id * 1.0f));

				shader->SetChangesFrame(lightDirection);
				shader->SetMaterial(materialAmbient, materialDiffuse);
				shader->SetLight(lightAmbient, lightDiffuse);

				shader->SetRendering();
			}, 0);

	}
}