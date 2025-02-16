
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert�s�N�Z���V�F�[�_�[
// 
// �����	: amateurK
// �쐬��	: 2024/08/02
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Texture2D textureDiffuse : register(t0);
SamplerState samplerPoint : register(s0);

//--------------------------------------------------------------------------------------
void LambertPS(
	in float4 inPosition : SV_Position,
	in float4 inColor : COLOR0,
	in float2 inTexcoord : TEXCOORD0,
	out float4 outColor : SV_Target
)
{
	outColor = textureDiffuse.Sample(samplerPoint, inTexcoord) * inColor;
	
	// �e�N�X�`���e�X�g�p
	//outColor = float4(inTexcoord.xy, 1, 1);

}