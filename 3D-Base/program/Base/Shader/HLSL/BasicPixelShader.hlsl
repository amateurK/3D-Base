
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���ʂ̃s�N�Z���V�F�[�_�[
// 
// �����	: amateurK
// �쐬��	: 2024/12/08
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Texture2D textureDiffuse : register(t0);
SamplerState samplerPoint : register(s0);

//--------------------------------------------------------------------------------------
void BasicPS(
	in float4 inPosition : SV_Position,
	in float4 inColor : COLOR0,
	out float4 outColor : SV_Target
)
{
	outColor = inColor;
}