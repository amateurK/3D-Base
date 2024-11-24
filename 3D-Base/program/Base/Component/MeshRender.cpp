
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 3Dモデルを描画するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2024/11/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "MeshRender.h"
#include "../Shader/Shader.h"
#include "../Model/Mesh/Mesh.h"
#include "../Model/Mesh/MeshManager.h"
#include "../Shader/LambertShader.h"

namespace AK_Base {

	//--------------------------------------------------------------------------------------
	MeshRender::MeshRender(Actor* const parent, std::wstring fileName)
		: Component(parent)
		, m_Transform(nullptr)
		, m_Shader(nullptr)
		, m_Mesh(nullptr)
	{
		m_Transform = GetActor()->GetComponent<Transform>();

		CreateResource(fileName);
	}

	//--------------------------------------------------------------------------------------
	void MeshRender::Render(const double& totalTime, const float& elapsedTime)
	{

		BaseWindow& bw(BaseWindow::GetInstance());
		ID3D11DeviceContext* d3dDeviceContext = bw.GetImmediateContext();

		XMVECTOR lightDirection = { 0.0f, 0.0f, 3.0f, 1.0f };
		XMFLOAT4 lightAmbient = { 0.1f, 0.1f, 0.1f, 1.0f };
		XMFLOAT4 lightDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		XMFLOAT4 materialAmbient = { 1.0f, 1.0f, 1.0f, 1.0f };
		XMFLOAT4 materialDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f };

		m_Mesh->Render(d3dDeviceContext, [&](int id, const std::vector<Mesh::MeshData> material)
			{
				auto shader = (Shader::LambertShader*)(m_Shader);
				shader->SetWorldMatrix(m_Transform->GetWorldMatrix());
				//shader->SetWorldMatrix(worldMatrix * DirectX::XMMatrixTranslation(0.0f, 0.0f, id * 1.0f));

				shader->SetChangesFrame(lightDirection);
				shader->SetMaterial(materialAmbient, materialDiffuse);
				shader->SetLight(lightAmbient, lightDiffuse);

				shader->SetRendering();
			}, 0);
	}


	//--------------------------------------------------------------------------------------
	HRESULT MeshRender::CreateResource(std::wstring fileName)
	{
		HRESULT hr = S_OK;

		hr = Mesh::MeshManager::GetInstance()->CreateMesh(fileName, m_Mesh);
		if (FAILED(hr))
			return hr;

		return hr;
	}
}