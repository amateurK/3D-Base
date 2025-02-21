
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 3Dモデルを描画するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2024/11/23
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "MeshRender.h"
#include "../Model/Mesh/Mesh.h"
#include "../Model/Mesh/MeshManager.h"
#include "../Shader/ShaderManager.h"
#include "../Shader/VertexShader/LambertVS.h"
#include "../Shader/VertexShader/BasicVS.h"

using namespace DirectX;

namespace AK_Base {

	//--------------------------------------------------------------------------------------
	MeshRender::MeshRender(Actor* const parent, std::wstring fileName)
		: Component(parent)
		, m_ShaderSet(nullptr)
		, m_Mesh(nullptr)
	{

		CreateResource(fileName);

	}

	//--------------------------------------------------------------------------------------
	void MeshRender::Render(const double& totalTime, const float& elapsedTime)
	{

		BaseWindow& bw(BaseWindow::GetInstance());
		ID3D11DeviceContext* d3dDeviceContext = bw.GetImmediateContext();

		m_Mesh->Render(d3dDeviceContext, [&](int id, const std::vector<Mesh::MeshData> material)
			{
				m_ShaderSet->SetData<const XMMATRIX*>("worldMatrix", m_ParentActor->GetTransform()->GetWorldMatrix());
				//const auto mat = *(m_ParentActor->GetTransform()->GetWorldMatrix()) * DirectX::XMMatrixTranslation(0.0f, 0.0f, id * 1.0f);
				//m_ShaderSet->SetData<const XMMATRIX*>("worldMatrix", &mat);
				
				// 描画順を変更できるようになったら分離
				m_ShaderSet->SetPerObject();
				m_ShaderSet->SetShaders();
				
			}, 0);
	}

	//--------------------------------------------------------------------------------------
	void MeshRender::SetShader(const std::string& name)
	{
		auto shaderM = Shader::ShaderManager::GetInstance();
		m_ShaderSet = shaderM->GetShaderSet(name);
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