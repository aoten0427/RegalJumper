#include "Base/Shader/Model.hlsli"
#include"CookTorrance.hlsli"

//	C++側から設定されるデータ②
Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

cbuffer ConstantBuffer : register(b2)
{
    float2 time : packoffset(c0);
    float2 centerHeight : packoffset(c1);
}

float4 main(PS_INPUT input) : SV_TARGET
{
    ////	指定された画像の表示
    float4 color = tex.Sample(samLinear, input.Tex);
    //ライティング計算
    color *= CookTorrance(input);
    color.a = 1;
    
    float4 color2 = tex2.Sample(samLinear, input.Tex);
    float4 blue = float4(0.4f, 0.9f, 1.0f, 1.0f);
    blue.rgb *= color2.r + color2.g + color.b;
    
    
    
    
    bool flag1 = step(input.WorldPosition.y, time.y + 1.8f - time.x);
    bool flag2 = step(input.WorldPosition.y, time.y + 3.4f - time.x);
    
    float alpha = min(0.5f, input.WorldPosition.y - (time.y + 1.8f - time.x));
    
    alpha = lerp(alpha, 0.5f, flag1);
    
    color = lerp(color + blue * alpha, color, flag1);
    color.a = flag2;
    
    return color;
}