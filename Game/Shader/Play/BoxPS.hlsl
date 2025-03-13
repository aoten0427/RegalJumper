cbuffer Parameters : register(b0)
{
    float4 DiffuseColor : packoffset(c0);
    float3 EmissiveColor : packoffset(c1);
    float3 SpecularColor : packoffset(c2);
    float SpecularPower : packoffset(c2.w);

    float3 LightDirection[3] : packoffset(c3);
    float3 LightDiffuseColor[3] : packoffset(c6);
    float3 LightSpecularColor[3] : packoffset(c9);

    float3 EyePosition : packoffset(c12);

    float3 FogColor : packoffset(c13);
    float4 FogVector : packoffset(c14);

    float4x4 World : packoffset(c15);
    float3x3 WorldInverseTranspose : packoffset(c19);
    float4x4 WorldViewProj : packoffset(c22);
};

cbuffer Shadow : register(b1)
{
    float4 PlayerPosition;
}

//VS
struct VS_INPUT
{
    float3 Pos : POSITION;
    float3 Normal : NORMAL;
    float3 Tangetnt : TANGENT;
    float4 Color : COLOR;
    float2 Tex : TEXCOORD;
};

//PS
struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Normal : NORMAL;
    float2 Tex : TEXCOORD;
    float3 LocalPosition : LOCALPOSITION;
    float3 WorldPosition : WORLDPOSITION;
    float3 EyeVector : EYEVECTOR;
};

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);


float4 main(PS_INPUT input) : SV_TARGET
{
    float2 offset = input.WorldPosition.xz - PlayerPosition.xz;
    float distSquared = dot(offset, offset);
    
    float mask1 = step(4.0, distSquared); //”ÍˆÍ”»’è
    float mask2 = step(input.Normal.y > 0.0001f,0);//ã•ûŒü”»’è
    float mask3 = step(PlayerPosition.y, input.WorldPosition.y);//ã‰º”»’è

    float mask = max(max(mask1, mask2),mask3); // ‚Ç‚¿‚ç‚©‚ª1‚È‚ç”’i1j
    
    return lerp(float4(0.2, 0.2, 0.5, 1), float4(0.1, 0.1, 0.1, 1), mask);
}