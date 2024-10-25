
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert���_�V�F�[�_�[
// 
// �����	: amateurK
// �쐬��	: 2024/08/02
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

cbuffer ChangesFrame : register(b0)
{
    // WorldViewProjection
	matrix matWVP;
    // ���[�J�����W�n�ł̌��̃x�N�g��
	float4 LightDirection;
}

cbuffer Material : register(b1)
{
    // �����W��
	float4 MaterialAmbient = { 1.0f, 1.0f, 1.0f, 1.0f };
	float4 MaterialDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
}

cbuffer Light : register(b2)
{
    // ���̋���
	float4 LightAmbient = { 0.2f, 0.2f, 0.2f, 0.0f };
	float4 LightDiffuse = { 0.8f, 0.8f, 0.8f, 0.0f };
}

//--------------------------------------------------------------------------------------
void main(
	in float4 inPosition : POSITION,
	in float3 inNormal : NORMAL,
	in float2 inTexcoord : TEXCOORD0,
	out float4 outPosition : SV_POSITION,
	out float4 outColor : COLOR0,
	out float2 outTexcoord : TEXCOORD0
)
{
	// ���W�ϊ�
	outPosition = mul(inPosition, matWVP);
	
	// ���_�F
	outColor = LightAmbient * MaterialAmbient
		+ LightDiffuse * MaterialDiffuse * saturate(dot(inNormal, LightDirection.xyz));
	
	// �e�N�X�`�����W
	outTexcoord = inTexcoord;
}