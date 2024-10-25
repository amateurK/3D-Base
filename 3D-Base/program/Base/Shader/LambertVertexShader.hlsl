
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Lambert頂点シェーダー
// 
// 製作者	: amateurK
// 作成日	: 2024/08/02
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
	// 座標変換
	outPosition = mul(inPosition, matWVP);
	
	// 頂点色
	outColor = LightAmbient * MaterialAmbient
		+ LightDiffuse * MaterialDiffuse * saturate(dot(inNormal, LightDirection.xyz));
	
	// テクスチャ座標
	outTexcoord = inTexcoord;
}