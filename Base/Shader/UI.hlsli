//表示データー
cbuffer ConstBuffer : register(b0)
{
    //中心位置
    float4 position;
    //画面サイズ
    float2 windowSize;
    //大きさ
    float2 size;
    //色
    float4 color;
    //表示幅
    float2 extent;
    //オフセット(0,0)左上原点,(0.5,0.5)原点変化なし,(1,1)右下原点
    float2 offset;
    //切り取り範囲
    float4 clipRange;
    //自由
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