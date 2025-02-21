
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// シェーダーを管理するマネージャークラス
// シングルトンクラス
// 
// 製作者	: amateurK
// 作成日	: 2024/11/29
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "ShaderManager.h"

using namespace DirectX;

namespace Shader {

	ShaderManager* ShaderManager::Instance = nullptr;

	ShaderManager::ShaderManager()
		: m_VPMatrix(XMMatrixIdentity())
	{
		m_ShaderList.clear();
		m_ShaderSetList.clear();
	}

	//--------------------------------------------------------------------------------------
	ShaderManager::~ShaderManager()
	{
		for (auto& shaderset : m_ShaderSetList) {
			delete shaderset.second;
		}
		for (auto& shader : m_ShaderList) {
			delete shader.second;
		}
	}

	//--------------------------------------------------------------------------------------
	ShaderSet* ShaderManager::AddShaderSet(
		const std::string& setName,
		const std::unordered_map<ShaderType, std::string>& nameList
	)
	{
		auto newSet = new ShaderSet();

		for (auto& shader : nameList) {
			auto ptr = GetShader(shader.second);
			newSet->AddShader(shader.first, ptr);
			ptr->AddDataForShaderSet(newSet);
		}

		m_ShaderSetList[setName] = newSet;
		newSet->SetName(setName);

		return newSet;
	}


	//--------------------------------------------------------------------------------------
	void ShaderManager::SetVPMatrix(const XMMATRIX& view, const XMMATRIX& proj)
	{
		m_VPMatrix = view * proj;
	}

	//---------------------------------------------------------------------------------------------
	ShaderSet* ShaderManager::CopyShaderSet(const std::string& name, const std::string& copyName)
	{
		// 複製する
		auto newSet = m_ShaderSetList[name]->Clone(copyName);

		m_ShaderSetList[copyName] = newSet;

		return newSet;
	}
}