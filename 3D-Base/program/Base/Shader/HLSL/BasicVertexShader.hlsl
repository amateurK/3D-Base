
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���ʂ̒��_�V�F�[�_�[
// 
// �����	: amateurK
// �쐬��	: 2024/12/08
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

cbuffer ChangesFrame : register(b0)
{
    // WorldViewProjection
	matrix matWVP;
}

cbuffer Material : register(b1)
{
	// ��Z����F
	float4 color;
}

//--------------------------------------------------------------------------------------
void BasicVS(
	in float4 inPosition : POSITION,
	in float4 inColor : COLOR0,
	out float4 outPosition : SV_POSITION,
	out float4 outColor : COLOR0
)
{
	// ���W�ϊ�
	outPosition = mul(inPosition, matWVP);
	
	// ���_�F
	outColor = color;
}