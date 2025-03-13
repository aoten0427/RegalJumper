#include"Model.hlsli"
#include"TestShadow.hlsli"

PS_SMD_INPUT main(VS_INPUT input)
{
	/* 手順８ */

    PS_SMD_INPUT output;

    // 頂点の位置を投影空間へ
    output.PositionPS = mul(float4(input.Pos,1), WorldViewProj);
    
    // 頂点の位置をワールド空間へ
    output.PositionWS = mul(float4(input.Pos, 1), World);
    
    // 法線ベクトルをワールド空間へ（拡大縮小の影響を打ち消すため逆転置行列をかける）
    output.NormalWS = mul(input.Normal, WorldInverseTranspose);
    normalize(output.NormalWS);
    
    // テクスチャのUV座標
    output.TexCoord = input.Tex;
    
    // 頂点の位置をライトの投影空間へ
    output.LightPosPS = mul(output.PositionWS, lightViewProjection);
 
    return output;
}