#include "Base/Shader/Model.hlsli"
#include"CookTorrance.hlsli"

//	C++側から設定されるデータ②
Texture2D tex : register(t0);
SamplerState samLinear : register(s0);



float4 main(PS_INPUT input) : SV_TARGET
{
    ////	指定された画像の表示
    float4 color = tex.Sample(samLinear, input.Tex);
    
    color *= CookTorrance(input);
    color.a = 1;
    
    return color;
}