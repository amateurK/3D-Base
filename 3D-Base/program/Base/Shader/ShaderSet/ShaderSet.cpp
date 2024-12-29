
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 使用するシェーダーを保持するクラス
// 
// 
// 製作者	: amateurK
// 作成日	: 2024/11/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "ShaderSet.h"

namespace Shader
{

	ShaderSet::ShaderSet()
	{
		m_ShaderList.clear();
	}

	//--------------------------------------------------------------------------------------
	ShaderSet::~ShaderSet()
	{

	}

	//---------------------------------------------------------------------------------------------
	ShaderSet* ShaderSet::Clone(const std::string& copyName)
	{
		ShaderSet* newSet = new ShaderSet();

		newSet->m_ShaderList = this->m_ShaderList;
		newSet->m_Data = this->m_Data;

		newSet->m_Name = copyName;

		return newSet;
	}

	//--------------------------------------------------------------------------------------
	void ShaderSet::SetShaders()
	{
		// 全シェーダーのシェーダーをセット
		for (auto& shader : m_ShaderList) {
			shader.second->SetShader(this);
		}
	}

	//--------------------------------------------------------------------------------------
	void ShaderSet::SetPerObject()
	{
		// 全シェーダーのシェーダーをセット
		for (auto& shader : m_ShaderList) {
			shader.second->SetPerObject(this);
		}
	}

	//--------------------------------------------------------------------------------------
	void ShaderSet::AddShader(ShaderType type, ShaderBase* shader)
	{
		m_ShaderList[type] = shader;
	}
}