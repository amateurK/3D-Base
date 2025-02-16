
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert頂点シェーダー
// スキニングアニメーションも行う
// 
// 製作者	: amateurK
// 作成日	: 2025/02/14
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

cbuffer ChangesFrame : register(b0)
{
    // WorldViewProjection
	matrix matWVP;
    // ローカル座標系での光のベクトル
	float4 LightDirection;
}

cbuffer Material : register(b1)
{
    // 反発係数
	float4 MaterialAmbient = { 1.0f, 1.0f, 1.0f, 1.0f };
	float4 MaterialDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
}

cbuffer Light : register(b2)
{
    // 光の強さ
	float4 LightAmbient = { 0.2f, 0.2f, 0.2f, 0.0f };
	float4 LightDiffuse = { 0.8f, 0.8f, 0.8f, 0.0f };
}

cbuffer Bones : register(b3)
{
	// ボーン行列
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
	// ボーン変形の適応
	float4x4 skinMatrix =
		mul(matBones[inBoneIndices.x], inBoneWeights.x)
		+ mul(matBones[inBoneIndices.y], inBoneWeights.y)
		+ mul(matBones[inBoneIndices.z], inBoneWeights.z)
		+ mul(matBones[inBoneIndices.w], inBoneWeights.w);
	
	// 座標変換
	float4 world = mul(inPosition, skinMatrix);
	outPosition = mul(world, matWVP);
	
	float3 transformedNormal = normalize(mul(inNormal, (float3x3) skinMatrix));
	
	// 頂点色
	outColor = LightAmbient * MaterialAmbient
		+ LightDiffuse * MaterialDiffuse * saturate(dot(transformedNormal, LightDirection.xyz));
	
	// テクスチャ座標
	outTexcoord = inTexcoord;
}