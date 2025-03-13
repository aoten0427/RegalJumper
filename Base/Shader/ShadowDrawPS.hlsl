/*
	���C�gwith�V���h�E�}�b�v�p�s�N�Z���V�F�[�_
*/
#include"Model.hlsli"
#include"TestShadow.hlsli"

Texture2D<float4> Texture : register(t0);
sampler Sampler : register(s0);




float4 main(PS_SMD_INPUT input) : SV_TARGET0
{
    // �@���𐳋K������
    float3 normal = normalize(input.NormalWS);
    /*
        �E���ׂ�������Ȃ�A���_�V�F�[�_�Ōv�Z����
        �E���x��������Ȃ�A�s�N�Z���V�F�[�_�Ōv�Z����
    */

    
    

    // ----------------------------------------------------------- //
    // �f�B�t���[�Y
    // ----------------------------------------------------------- //
 
	/* �菇�X */

    // ���C�g���Ƃ炷�������v�Z����
    //float3 lightDir = normalize(input.PositionWS.xyz - lightPosition.xyz);
    float3 lightDir = normalize(lightDirirection);
    
    // ���C�g�֌������x�N�g��
    float3 toLight = (-lightDir);

    // ���̋�������ς���Z�o����
    float intensity1 = max(dot(normal, toLight), 0.0f);

    float shadow = ShadowMap(input);

    // ���C�g�Ɖe�ɂ�閾�邳���v�Z����
    //float3 lightAmount = shadow * (1.0f - lightAmbient) + lightAmbient;
    float3 lightAmount = lerp(lightAmbient, float3(1.0f, 1.0f, 1.0f), shadow);
    lightAmount *= intensity1;

    // �g�U���ːF�����߂� 
    float3 diffuse = DiffuseColor.rgb * lightAmount;

        
    // ----------------------------------------------------------- //
    // �X�y�L����
    // ----------------------------------------------------------- //
    
	/* �菇�P�O */
    
    // �����x�N�g��
    float3 toEye = normalize(EyePosition - input.PositionWS.xyz);

    // �n�[�t�x�N�g�����J�������W�{���C�g���W
    float3 halfVector = normalize(toEye + toLight);

    // ���ʔ��˂̉e����������ς��g���v�Z����
    float intensity2 = max(dot(normal, halfVector), 0.0f);

    // �X�y�L�����p���[���w���Ƃ��Ďg���n�C���C�g�̂������𒲐�����
    float3 specular = pow(intensity2, SpecularPower) * SpecularColor;
    
    // �e�̉e�����l������
    specular *= shadow;
 
    
    // ----------------------------------------------------------- //
    // �ŏI�J���[
    // ----------------------------------------------------------- //

    // �e�N�X�`���J���[���T���v������
    float4 textureColor = /*Texture.Sample(Sampler, input.TexCoord)*/float4(1,1,1,1);
    
    // �e�N�X�`���̐F�Ɋg�U���˂Ƌ��ʔ��˂𔽉f����
    float3 finalColor = textureColor.rgb * diffuse + specular + lightAmbient;
    
    return float4(shadow, shadow, shadow, 1);
    
    return float4(finalColor, 1.0f);
}
