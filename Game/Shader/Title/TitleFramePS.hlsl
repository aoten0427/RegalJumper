#include "Base/Shader/UI.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

static const float range = 0.01f;
static const float harf = range / 2;

float4 main(PS_INPUT input) : SV_TARGET
{
    float2 uv = input.tex;
    float noiseY = uv.y + fmod(free.x, 1.0f);
    noiseY = fmod(noiseY, 1.0f);
    
    bool flag = step(noiseY, range);
    uv.x -= (harf - abs(noiseY - 0.005)) * 1.3f * flag;


    flag = step(noiseY, range + 0.5f) && step(0.5f, noiseY);
    uv.x += (harf - abs(noiseY - 0.505)) * 1.7f * flag;
    
	//	Žw’è‚³‚ê‚½‰æ‘œ‚Ì•\Ž¦
    float4 output = tex.Sample(samLinear, uv);
    
    output *= color;
    return output;
}