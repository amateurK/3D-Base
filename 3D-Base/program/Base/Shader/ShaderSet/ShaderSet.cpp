
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �g�p����V�F�[�_�[��ێ�����N���X
// 
// 
// �����	: amateurK
// �쐬��	: 2024/11/30
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

	//--------------------------------------------------------------------------------------
	void ShaderSet::SetShaders()
	{
		// �S�V�F�[�_�[�̃V�F�[�_�[���Z�b�g
		for (auto& shader : m_ShaderList) {
			shader.second->SetShader(this);
		}
	}

	//--------------------------------------------------------------------------------------
	void ShaderSet::SetPerObject()
	{
		// �S�V�F�[�_�[�̃V�F�[�_�[���Z�b�g
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