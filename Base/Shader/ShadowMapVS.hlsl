#include"Model.hlsli"
#include"TestShadow.hlsli"

// メイン関数
PS_SM_INPUT main(VS_SM_INPUT input)
{
    /* 手順１ */

    PS_SM_INPUT output;
    
    output.Position = mul(input.Position, WorldViewProj);
    
    return output;
}