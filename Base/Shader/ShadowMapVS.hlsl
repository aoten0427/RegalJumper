#include"Model.hlsli"
#include"TestShadow.hlsli"

// ���C���֐�
PS_SM_INPUT main(VS_SM_INPUT input)
{
    /* �菇�P */

    PS_SM_INPUT output;
    
    output.Position = mul(input.Position, WorldViewProj);
    
    return output;
}