#include "UI.hlsli"

static const unsigned int vnum = 4;

//	wが0だと行列計算がおかしくなるので1に変更
static const float4 offset_array[vnum] =
{
    float4(-1.0f, 1.0f, 0.0f, 1.0f), //	左上
	float4(1.0f, 1.0f, 0.0f, 1.0f), //	右上
	float4(-1.0f, -1.0f, 0.0f, 1.0f), //	左下
	float4(1.0f, -1.0f, 0.0f, 1.0f), //	右下

};

static const float2 offset_UV[vnum] =
{
    float2(0.0f, 0.0f), //	左上
	float2(1.0f, 0.0f), //	右上
	float2(0.0f, 1.0f), //	左下
	float2(1.0f, 1.0f), //	右下

};

static const float2 origin = float2(-1, 1);

[maxvertexcount(vnum)]
void main(
	point PS_INPUT input[1],
	inout TriangleStream<PS_INPUT> output
)
{

    for (uint i = 0; i < vnum; i++)
    {
		//	ジオメトリ出力
        PS_INPUT element;
		
		//ウィンドウサイズ
        float2 window = windowSize.xy;
		//ポジションを相対スケールに変換
        float2 Position = input[0].pos.xy / window * 2.0f;
		//原点から位置を計算.
        Position = float2(origin.x + Position.x, origin.y - Position.y);
		
		//サイズを計算
        float2 relativeSize = size / window;
		
        
		//オフセット一から四隅を計算
        float2 offsetPar = offset / 0.5f;
        float2 offsetPos = float2(1 - offsetPar.x, -1 + offsetPar.y);
        float2 corner = offset_array[i].xy + offsetPos;
		
		//最終位置を計算
        element.pos.xy = Position + corner * relativeSize * extent;
		
		
        element.pos.z = 0.0f;
        element.pos.w = 1.0f;

		//	テクスチャのUV座標
        element.tex = float2(clipRange.x + clipRange.z * offset_UV[i].x, clipRange.y + clipRange.w * offset_UV[i].y);
        
        output.Append(element);
    }
    output.RestartStrip();
}