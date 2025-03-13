#include "Base/Shader/Model.hlsli"
#include"CookTorrance.hlsli"

//	C++������ݒ肳���f�[�^�A
Texture2D tex : register(t0);
SamplerState samLinear : register(s0);



float4 main(PS_INPUT input) : SV_TARGET
{
    ////	�w�肳�ꂽ�摜�̕\��
    float4 color = tex.Sample(samLinear, input.Tex);
    
    color *= CookTorrance(input);
    color.a = 1;
    
    return color;
}