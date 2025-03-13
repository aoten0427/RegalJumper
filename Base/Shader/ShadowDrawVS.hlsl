#include"Model.hlsli"
#include"TestShadow.hlsli"

PS_SMD_INPUT main(VS_INPUT input)
{
	/* �菇�W */

    PS_SMD_INPUT output;

    // ���_�̈ʒu�𓊉e��Ԃ�
    output.PositionPS = mul(float4(input.Pos,1), WorldViewProj);
    
    // ���_�̈ʒu�����[���h��Ԃ�
    output.PositionWS = mul(float4(input.Pos, 1), World);
    
    // �@���x�N�g�������[���h��Ԃցi�g��k���̉e����ł��������ߋt�]�u�s���������j
    output.NormalWS = mul(input.Normal, WorldInverseTranspose);
    normalize(output.NormalWS);
    
    // �e�N�X�`����UV���W
    output.TexCoord = input.Tex;
    
    // ���_�̈ʒu�����C�g�̓��e��Ԃ�
    output.LightPosPS = mul(output.PositionWS, lightViewProjection);
 
    return output;
}