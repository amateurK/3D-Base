
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert���_�V�F�[�_�[
// �X�L�j���O�A�j���[�V�������s��
// 
// �����	: amateurK
// �쐬��	: 2025/02/14
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

cbuffer Bones : register(b3)
{
	// �{�[���s��
	matrix matBones[100];
}

//--------------------------------------------------------------------------------------
void LambertSkinningVS(
	in float4 inPosition : POSITION,
	in float3 inNormal : NORMAL,
	in float2 inTexcoord : TEXCOORD0,
	in uint4 inBoneIndices : BLENDINDICES0,
	in float4 inBoneWeights : BLENDWEIGHT0,
	out float4 outPosition : SV_POSITION,
	out float4 outColor : COLOR0,
	out float2 outTexcoord : TEXCOORD0
)
{
	// �{�[���ό`�̓K��
	float4x4 skinMatrix =
		mul(matBones[inBoneIndices.x], inBoneWeights.x)
		+ mul(matBones[inBoneIndices.y], inBoneWeights.y)
		+ mul(matBones[inBoneIndices.z], inBoneWeights.z)
		+ mul(matBones[inBoneIndices.w], inBoneWeights.w);
	
	// ���W�ϊ�
	float4 world = mul(inPosition, skinMatrix);
	outPosition = mul(world, matWVP);
	
	float3 transformedNormal = normalize(mul(inNormal, (float3x3) skinMatrix));
	
	// ���_�F
	outColor = LightAmbient * MaterialAmbient
		+ LightDiffuse * MaterialDiffuse * saturate(dot(transformedNormal, LightDirection.xyz));
	
	// �e�N�X�`�����W
	outTexcoord = inTexcoord;
}