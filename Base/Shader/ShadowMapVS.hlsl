#include"Model.hlsli"
#include"TestShadow.hlsli"

// ƒƒCƒ“ŠÖ”
PS_SM_INPUT main(VS_SM_INPUT input)
{
    /* è‡‚P */

    PS_SM_INPUT output;
    
    output.Position = mul(input.Position, WorldViewProj);
    
    return output;
}