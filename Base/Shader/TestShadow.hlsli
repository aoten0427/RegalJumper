#include"Model.hlsli"
/*
    共通で使用するパラメータ
*/
#ifndef TESTSHASOW_HLSLI
#define TESTSHASOW_HLSLI

// ライト用定数バッファ
cbuffer LightParameters : register(b1)
{
    float4x4 lightViewProjection : packoffset(c0);
    float4 lightPosition : packoffset(c4);
    float3 lightDirirection : packoffset(c5);
    float3 lightAmbient : packoffset(c6);
};



// ピクセルシェーダ入力用
struct PS_SMD_INPUT
{
    float2 TexCoord : TEXCOORD0;
    float4 PositionWS : TEXCOORD1;
    float3 NormalWS : TEXCOORD2;
    float4 LightPosPS : TEXCOORD3;
    float4 PositionPS : SV_Position;
};

// シャドウマップの頂点シェーダ入力用
struct VS_SM_INPUT
{
    float4 Position : SV_Position;
};

// シャドウマップのピクセルシェーダ入力用
struct PS_SM_INPUT
{
    float4 Position : SV_Position;
};

// シャドウマップテクスチャ
Texture2D ShadowMapTexture : register(t1);

// シャドウマップ用テクスチャサンプラー
SamplerComparisonState ShadowMapSampler : register(s1);

// マッハバンド対策
//#define SHADOW_EPSILON 0.0005f
static const float SHADOW_EPSILON = 0.002f;

float ShadowMap(PS_SMD_INPUT input)
{
    float3 vec = lightDirirection;
    normalize(vec);
    
    //if (dot(input.NormalWS, vec) > 0)
    //    return 0;
    
    // 正規化デバイス座標にする
    input.LightPosPS.xyz /= input.LightPosPS.w;

    //// UV座標がシャドウマップ内にあるか確認
    //if (input.LightPosPS.x < 0.0f || input.LightPosPS.x > 1.0f || input.LightPosPS.y < 0.0f || input.LightPosPS.y > 1.0f)
    //{
    //    // UV座標が範囲外なら影の計算をスキップ
    //    return 1.0f; // 範囲外のピクセルは影なしとする
    //}
    
    // 現在のピクセルがシャドウマップ上でどの位置にあたるか計算する
    float2 uv = input.LightPosPS.xy * float2(0.5f, -0.5f) + 0.5f;

      // UV座標がシャドウマップ内にあるか確認
    //if (uv.x < 0.0f || uv.x > 1.0f || uv.y < 0.0f || uv.y > 1.0f)
    //{
    //    // UV座標が範囲外なら影の計算をスキップ
    //    return 1.0f; // 範囲外のピクセルは影なしとする
    //}
    
    float len = length((input.PositionWS - lightPosition));
    //if (len > 400)
    //    return 1.0f;
    float par = 0.5f / (len * (len  / 1000.0f));
    
  
    //float par = 1.0f;
    // 通常描画の深度値とライト空間の深度値を比較して影になるか調べる
    // ShadowMapTextureの該当する場所の深度値と現在のピクセルの深度値を比較して、影になるか調べる
    // shadow　0.0f：影がある、1.0f：影がない
    float shadow = ShadowMapTexture.SampleCmpLevelZero(
        ShadowMapSampler, uv, input.LightPosPS.z - (SHADOW_EPSILON * par)).
    x;
    return shadow;
}

#endif