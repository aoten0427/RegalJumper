#include"Model.hlsli"

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;
    //テクスチャ情報セット
    output.Tex = input.Tex;
    //法線情報セット
    output.Normal = input.Normal;
    //ローカルポジションセット
    output.LocalPosition = input.Pos.xyz;
    //ワールドポジションセット
    output.Pos = mul(float4(input.Pos, 1), WorldViewProj);
    output.WorldPosition = mul(float4(input.Pos, 1),World).xyz;
    
    output.EyeVector = (output.WorldPosition.xyz - EyePosition);
    
    return output;
}