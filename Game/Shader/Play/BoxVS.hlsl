

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

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;
    //テクスチャ情報セット
    output.Tex = input.Tex;
    //法線情報セット
    output.Normal = mul(input.Normal, WorldInverseTranspose);
    //ローカルポジションセット
    output.LocalPosition = input.Pos.xyz;
    //ワールドポジションセット
    output.Pos = mul(float4(input.Pos, 1), WorldViewProj);
    output.WorldPosition = mul(float4(input.Pos, 1), World).xyz;
    
    output.EyeVector = (output.WorldPosition.xyz - EyePosition);
    
    return output;
}