#include"Model.hlsli"
#include"TestShadow.hlsli"

float4 main(PS_SM_INPUT input) : SV_TARGET
{
    //float shadow = input.Position.z * input.Position.z * input.Position.z * input.Position.z * input.Position.z * input.Position.z;
    //return float4(shadow, shadow, shadow, 1.0);
    return float4(input.Position.z, input.Position.z, input.Position.z, 1.0f);
}