#include "UI.hlsli"

static const unsigned int vnum = 4;

//	w��0���ƍs��v�Z�����������Ȃ�̂�1�ɕύX
static const float4 offset_array[vnum] =
{
    float4(-1.0f, 1.0f, 0.0f, 1.0f), //	����
	float4(1.0f, 1.0f, 0.0f, 1.0f), //	�E��
	float4(-1.0f, -1.0f, 0.0f, 1.0f), //	����
	float4(1.0f, -1.0f, 0.0f, 1.0f), //	�E��

};

static const float2 offset_UV[vnum] =
{
    float2(0.0f, 0.0f), //	����
	float2(1.0f, 0.0f), //	�E��
	float2(0.0f, 1.0f), //	����
	float2(1.0f, 1.0f), //	�E��

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
		//	�W�I���g���o��
        PS_INPUT element;
		
		//�E�B���h�E�T�C�Y
        float2 window = windowSize.xy;
		//�|�W�V�����𑊑΃X�P�[���ɕϊ�
        float2 Position = input[0].pos.xy / window * 2.0f;
		//���_����ʒu���v�Z.
        Position = float2(origin.x + Position.x, origin.y - Position.y);
		
		//�T�C�Y���v�Z
        float2 relativeSize = size / window;
		
        
		//�I�t�Z�b�g�ꂩ��l�����v�Z
        float2 offsetPar = offset / 0.5f;
        float2 offsetPos = float2(1 - offsetPar.x, -1 + offsetPar.y);
        float2 corner = offset_array[i].xy + offsetPos;
		
		//�ŏI�ʒu���v�Z
        element.pos.xy = Position + corner * relativeSize * extent;
		
		
        element.pos.z = 0.0f;
        element.pos.w = 1.0f;

		//	�e�N�X�`����UV���W
        element.tex = float2(clipRange.x + clipRange.z * offset_UV[i].x, clipRange.y + clipRange.w * offset_UV[i].y);
        
        output.Append(element);
    }
    output.RestartStrip();
}