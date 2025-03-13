#include"Model.hlsli"
/*
    ���ʂŎg�p����p�����[�^
*/
#ifndef TESTSHASOW_HLSLI
#define TESTSHASOW_HLSLI

// ���C�g�p�萔�o�b�t�@
cbuffer LightParameters : register(b1)
{
    float4x4 lightViewProjection : packoffset(c0);
    float4 lightPosition : packoffset(c4);
    float3 lightDirirection : packoffset(c5);
    float3 lightAmbient : packoffset(c6);
};



// �s�N�Z���V�F�[�_���͗p
struct PS_SMD_INPUT
{
    float2 TexCoord : TEXCOORD0;
    float4 PositionWS : TEXCOORD1;
    float3 NormalWS : TEXCOORD2;
    float4 LightPosPS : TEXCOORD3;
    float4 PositionPS : SV_Position;
};

// �V���h�E�}�b�v�̒��_�V�F�[�_���͗p
struct VS_SM_INPUT
{
    float4 Position : SV_Position;
};

// �V���h�E�}�b�v�̃s�N�Z���V�F�[�_���͗p
struct PS_SM_INPUT
{
    float4 Position : SV_Position;
};

// �V���h�E�}�b�v�e�N�X�`��
Texture2D ShadowMapTexture : register(t1);

// �V���h�E�}�b�v�p�e�N�X�`���T���v���[
SamplerComparisonState ShadowMapSampler : register(s1);

// �}�b�n�o���h�΍�
//#define SHADOW_EPSILON 0.0005f
static const float SHADOW_EPSILON = 0.002f;

float ShadowMap(PS_SMD_INPUT input)
{
    float3 vec = lightDirirection;
    normalize(vec);
    
    //if (dot(input.NormalWS, vec) > 0)
    //    return 0;
    
    // ���K���f�o�C�X���W�ɂ���
    input.LightPosPS.xyz /= input.LightPosPS.w;

    //// UV���W���V���h�E�}�b�v���ɂ��邩�m�F
    //if (input.LightPosPS.x < 0.0f || input.LightPosPS.x > 1.0f || input.LightPosPS.y < 0.0f || input.LightPosPS.y > 1.0f)
    //{
    //    // UV���W���͈͊O�Ȃ�e�̌v�Z���X�L�b�v
    //    return 1.0f; // �͈͊O�̃s�N�Z���͉e�Ȃ��Ƃ���
    //}
    
    // ���݂̃s�N�Z�����V���h�E�}�b�v��łǂ̈ʒu�ɂ����邩�v�Z����
    float2 uv = input.LightPosPS.xy * float2(0.5f, -0.5f) + 0.5f;

      // UV���W���V���h�E�}�b�v���ɂ��邩�m�F
    //if (uv.x < 0.0f || uv.x > 1.0f || uv.y < 0.0f || uv.y > 1.0f)
    //{
    //    // UV���W���͈͊O�Ȃ�e�̌v�Z���X�L�b�v
    //    return 1.0f; // �͈͊O�̃s�N�Z���͉e�Ȃ��Ƃ���
    //}
    
    float len = length((input.PositionWS - lightPosition));
    //if (len > 400)
    //    return 1.0f;
    float par = 0.5f / (len * (len  / 1000.0f));
    
  
    //float par = 1.0f;
    // �ʏ�`��̐[�x�l�ƃ��C�g��Ԃ̐[�x�l���r���ĉe�ɂȂ邩���ׂ�
    // ShadowMapTexture�̊Y������ꏊ�̐[�x�l�ƌ��݂̃s�N�Z���̐[�x�l���r���āA�e�ɂȂ邩���ׂ�
    // shadow�@0.0f�F�e������A1.0f�F�e���Ȃ�
    float shadow = ShadowMapTexture.SampleCmpLevelZero(
        ShadowMapSampler, uv, input.LightPosPS.z - (SHADOW_EPSILON * par)).
    x;
    return shadow;
}

#endif