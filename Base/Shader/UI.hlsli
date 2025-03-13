//�\���f�[�^�[
cbuffer ConstBuffer : register(b0)
{
    //���S�ʒu
    float4 position;
    //��ʃT�C�Y
    float2 windowSize;
    //�傫��
    float2 size;
    //�F
    float4 color;
    //�\����
    float2 extent;
    //�I�t�Z�b�g(0,0)���㌴�_,(0.5,0.5)���_�ω��Ȃ�,(1,1)�E�����_
    float2 offset;
    //�؂���͈�
    float4 clipRange;
    //���R
    float4 free;
};

struct VS_INPUT
{
    float3 pos : POSITION;
    float2 tex : TEXCOORD;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};