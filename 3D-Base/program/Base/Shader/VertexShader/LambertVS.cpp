
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert���_�V�F�[�_�[
// 
// �����	: amateurK
// �쐬��	: 2024/12/01
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "LambertVS.h"
#include "../ShaderManager.h"

namespace Shader {

	LambertVS::LambertVS()
		:VertexShader()
	{

	}
	//--------------------------------------------------------------------------------------
	LambertVS::~LambertVS()
	{

	}

	//--------------------------------------------------------------------------------------
	HRESULT LambertVS::Init(const ShaderInitParam& params)
	{
		HRESULT hr = S_OK;

		hr = __super::Init(params);
		if (FAILED(hr))return hr;

		// �R���X�^���g�o�b�t�@���Z�b�g
		CreateConstantBuffer(sizeof(ChangesFrame));
		CreateConstantBuffer(sizeof(Material));
		CreateConstantBuffer(sizeof(Light));

		return hr;
	}

	//--------------------------------------------------------------------------------------
	void LambertVS::SetChangeFrame(const XMMATRIX& world, const XMVECTOR& light)
	{
		// WVP�s����Z�o
		auto matWVP = world * *(ShaderManager::GetInstance()->GetVPMatrix());
		matWVP = XMMatrixTranspose(matWVP);

		// ���̌��������[�J�����W�ɕϊ�
		auto worldInv = XMMatrixInverse(nullptr, world);
		auto vecLight = XMVector4Transform(light, worldInv);	// ���[�J�����W�ɕϊ�
		vecLight = XMVector3Normalize(light);

		SetConstantBuffer<ChangesFrame>(0, matWVP, vecLight);
	}
}
