
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �X�L�j���O�A�j���[�V����������3D���f����`�悷��R���|�[�l���g
// 
// �����	: amateurK
// �쐬��	: 2025/02/13
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "SkinningMeshRender.h"
#include "MeshRender.h"
#include "../Model/Mesh/SkinningMesh.h"
#include "../Model/Mesh/MeshManager.h"
#include "../Shader/ShaderManager.h"
#include "../Shader/VertexShader/LambertVS.h"
#include "../Shader/VertexShader/BasicVS.h"
#include "../Model/Animation/AnimationManager.h"

using namespace DirectX;

namespace AK_Base {

	//--------------------------------------------------------------------------------------
	SkinningMeshRender::SkinningMeshRender(Actor* const parent, std::wstring fileName)
		: Component(parent)
		, m_ShaderSet(nullptr)
		, m_Mesh(nullptr)
		, m_AnimationData({ nullptr, 0.0f, 1.0f, false})
	{

		CreateResource(fileName);


	}

	//--------------------------------------------------------------------------------------
	void SkinningMeshRender::Render(const double& totalTime, const float& elapsedTime)
	{
		// ���Ԃ̍X�V
		m_AnimationData.Time += elapsedTime * m_AnimationData.Speed;
		if (m_AnimationData.Loop)
		{
			if (m_AnimationData.Time > m_AnimationData.Clip->GetDuration())
			{
				m_AnimationData.Time = 0.0f;
			}
		}

		// �{�[���̍s����X�V
		const auto bone = m_Mesh->GetBoneData();
		std::vector<DirectX::XMMATRIX> worldMatrices(bone.size());	// �ċA�p�̃��[���h�s��
		CalcBoneMatrices(&bone[0], DirectX::XMMatrixIdentity(), worldMatrices);

		// �V�F�[�_�[�̃{�[���̍s����X�V
		m_ShaderSet->SetData<const std::vector<DirectX::XMMATRIX>*>("BoneMatrices", &m_BoneMatrices);

		BaseWindow& bw(BaseWindow::GetInstance());
		ID3D11DeviceContext* d3dDeviceContext = bw.GetImmediateContext();

		m_Mesh->Render(d3dDeviceContext, [&](int id, const std::vector<Mesh::MeshData> material)
			{
				m_ShaderSet->SetData<const XMMATRIX*>("worldMatrix", m_ParentActor->GetTransform()->GetWorldMatrix());
				//const auto mat = *(m_ParentActor->GetTransform()->GetWorldMatrix()) * DirectX::XMMatrixTranslation(0.0f, 0.0f, id * 1.0f);
				//m_ShaderSet->SetData<const XMMATRIX*>("worldMatrix", &mat);

				// �`�揇��ύX�ł���悤�ɂȂ����番��
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
	void SkinningMeshRender::PlayAnimation(const std::wstring& fileName, float time, float speed, bool isLoop)
	{
		auto animM = Anim::AnimationManager::GetInstance();
		m_AnimationData.Clip = animM->CreateAnimation(fileName);
		m_AnimationData.Time = time;
		m_AnimationData.Speed = speed;
		m_AnimationData.Loop = isLoop;
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

	//--------------------------------------------------------------------------------------
	void SkinningMeshRender::CalcBoneMatrices(const Mesh::BoneData* bone,
		const DirectX::XMMATRIX& parentMatrix,
		std::vector<DirectX::XMMATRIX>& worldMatrices)
	{
		// �{�[���̃��[���h�ϊ��s����v�Z
		DirectX::XMMATRIX worldMatrix = parentMatrix;

		DirectX::XMMATRIX mat;
		// �A�j���[�V��������
		if (m_AnimationData.Clip != nullptr)
		{
			if (m_AnimationData.Clip->GetBoneMatrix(bone->Name, m_AnimationData.Time, mat))
			{
				//mat = DirectX::XMMatrixRotationX(-1.0f);
				//auto quat = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), -1.0f);
				//mat = DirectX::XMMatrixRotationQuaternion(quat);
				worldMatrix *= bone->LocalMatrix * mat;
			}
			else
			{
				worldMatrix *= bone->LocalMatrix;
			}
		}
		else
		{
			worldMatrix *= bone->LocalMatrix;
		}

		// �{�[���̃��[���h�ϊ��s���z��Ɋi�[
		worldMatrices[bone->ID] = worldMatrix;
		// �{�[���̍ŏI�s���z��Ɋi�[
		m_BoneMatrices[bone->ID] = worldMatrix * bone->InverseBindMatrix;

		// �q�{�[���̍s����v�Z
		if (bone->FirstChild != nullptr) {
			CalcBoneMatrices(bone->FirstChild, worldMatrix, worldMatrices);
		}
		// �Z��{�[���̍s����v�Z
		if (bone->NextSibling != nullptr) {
			CalcBoneMatrices(bone->NextSibling, parentMatrix, worldMatrices);
		}
	}
}