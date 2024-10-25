
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �V�F�[�_�[�N���X
// ���ۃN���X
// 
// �����	: amateurK
// �쐬��	: 2024/08/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Shader.h"
#include "../BaseWindow.h"

namespace Shader{

	Shader::Shader()
	{
		AK_Base::BaseWindow& bw(AK_Base::BaseWindow::GetInstance());
		m_D3DDevice = bw.GetD3DDevice();
		m_ImmediateContext = bw.GetImmediateContext();

		// �������z�֐��Ȃ̂ŁA����N���X�ł���Shader�N���X�ł͂����Ȃ�
		//Create();
	}

	//--------------------------------------------------------------------------------------
	Shader::~Shader()
	{
		m_VertexShader.Reset();
		m_PixelShader.Reset();
		m_VertexLayout.Reset();
		m_BlendState.Reset();
		m_Sampler.Reset();

	}
}