
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 普通の頂点シェーダー
// 
// 製作者	: amateurK
// 作成日	: 2024/12/08
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

cbuffer ChangesFrame : register(b0)
{
    // WorldViewProjection
	matrix matWVP;
}

cbuffer Material : register(b1)
{
	// 乗算する色
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
	// 座標変換
	outPosition = mul(inPosition, matWVP);
	
	// 頂点色
	outColor = color;
}