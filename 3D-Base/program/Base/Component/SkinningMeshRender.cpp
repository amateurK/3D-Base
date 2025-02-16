
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// スキニングアニメーションをする3Dモデルを描画するコンポーネント
// 
// 製作者	: amateurK
// 作成日	: 2025/02/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "SkinningMeshRender.h"
#include "MeshRender.h"
#include "../Model/Mesh/SkinningMesh.h"
#include "../Model/Mesh/MeshManager.h"
#include "../Shader/ShaderManager.h"
#include "../Shader/VertexShader/LambertVS.h"
#include "../Shader/VertexShader/BasicVS.h"

using namespace DirectX;

namespace AK_Base {

	//--------------------------------------------------------------------------------------
	SkinningMeshRender::SkinningMeshRender(Actor* const parent, std::wstring fileName)
		: Component(parent)
		, m_ShaderSet(nullptr)
		, m_Mesh(nullptr)
	{

		CreateResource(fileName);


	}

	//--------------------------------------------------------------------------------------
	void SkinningMeshRender::Render(const double& totalTime, const float& elapsedTime)
	{
		m_Mesh->UpdateBoneMatrices(m_BoneMatrices);
		m_ShaderSet->SetData<const std::vector<DirectX::XMMATRIX>*>("BoneMatrices", &m_BoneMatrices);

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
	void SkinningMeshRender::SetShader(const std::string& name)
	{
		auto shaderM = Shader::ShaderManager::GetInstance();
		m_ShaderSet = shaderM->GetShaderSet(name);
	}



	//--------------------------------------------------------------------------------------
	HRESULT SkinningMeshRender::CreateResource(std::wstring fileName)
	{
		HRESULT hr = S_OK;

		hr = Mesh::MeshManager::GetInstance()->CreateMesh(fileName, reinterpret_cast<Mesh::Mesh*&>(m_Mesh));
		if (FAILED(hr))
			return hr;

		m_BoneMatrices.resize(m_Mesh->GetBoneData().size());

		return hr;
	}
}