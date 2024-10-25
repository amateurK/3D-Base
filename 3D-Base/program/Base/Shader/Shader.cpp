
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// シェーダークラス
// 抽象クラス
// 
// 製作者	: amateurK
// 作成日	: 2024/08/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Shader.h"
#include "../BaseWindow.h"

namespace Shader{

	Shader::Shader()
	{
		AK_Base::BaseWindow& bw(AK_Base::BaseWindow::GetInstance());
		m_D3DDevice = bw.GetD3DDevice();
		m_ImmediateContext = bw.GetImmediateContext();

		// 純粋仮想関数なので、既定クラスであるShaderクラスではつかえない
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