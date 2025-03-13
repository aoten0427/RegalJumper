#include"Model.hlsli"

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;
    //�e�N�X�`�����Z�b�g
    output.Tex = input.Tex;
    //�@�����Z�b�g
    output.Normal = input.Normal;
    //���[�J���|�W�V�����Z�b�g
    output.LocalPosition = input.Pos.xyz;
    //���[���h�|�W�V�����Z�b�g
    output.Pos = mul(float4(input.Pos, 1), WorldViewProj);
    output.WorldPosition = mul(float4(input.Pos, 1),World).xyz;
    
    output.EyeVector = (output.WorldPosition.xyz - EyePosition);
    
    return output;
}