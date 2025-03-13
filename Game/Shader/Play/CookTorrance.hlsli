#include "Base/Shader/Model.hlsli"



cbuffer ConstantBuffer : register(b1)
{
    float4 lightPosition;        // �����̈ʒu (���[���h���W)
    float4 cameraPosition;       // �J�����̈ʒu (���[���h���W)
    float diffuseCoefficient;    // �g�U���ˌW��
    float ambientCoefficient;    // �����W��
    float specularCoefficient;   // ���ʔ��ˌW��
    float roughness;             // �e��
    float4 diffuseColor;         // �g�U���˂̐F
    float4 specularColor;        // ���ʔ��˂̐F
    float refractiveIndex;       // ���ܗ�
    float3 reserved;             // �\���̒l
}

// �e���ɂ��n�C���C�g���v�Z
float NormalDistributionFunction(float cosTheta)
{
    float alpha = roughness * roughness;
    float alpha2 = alpha * alpha;
    float cosTheta2 = cosTheta * cosTheta;

    float denominator = cosTheta2 * (alpha2 - 1.0) + 1.0;
    return alpha2 / (3.14159 * denominator * denominator);
}


// �􉽌��������v�Z
float SmithG(float cosTheta, float roughness)
{
    float alpha = roughness * roughness;
    float tanTheta = sqrt(1.0 - cosTheta * cosTheta) / cosTheta;
    float a = 1.0 / (alpha * tanTheta);
    return a < 1.6 ? (3.535 * a + 2.181 * a * a) / (1.0 + 2.276 * a + 2.577 * a * a) : 1.0;
}


// �􉽌����W�����v�Z
float GeometricAttenuationCoefficient(float3 normal, float3 viewDir, float3 halfDir, float3 lightDir)
{
    float Gv = SmithG(dot(normal, viewDir), roughness);
    float Gl = SmithG(dot(normal, lightDir), roughness);
    return Gv * Gl;
}


// �t���l�����ˌW�����v�Z
float FresnelReflectionCoefficient(float cosTheta, float eta)
{
    float c = abs(cosTheta);
    float g = sqrt(eta * eta + c * c - 1);
    float gMinusC = g - c;
    float gPlusC = g + c;
    return 0.5f * (gMinusC * gMinusC / (gPlusC * gPlusC)) *
           (1 + pow((c * gPlusC - 1) / (c * gMinusC + 1), 2));
}


// �N�b�N�g�����X���f��
float4 CookTorrance(PS_INPUT input)
{
    // �����ƃJ�����̈ʒu���擾
    float3 lightPos = lightPosition.xyz;
    float3 cameraPos = cameraPosition.xyz;

    // �@���A�����A�����A�n�[�t�x�N�g�����v�Z
    float3 normal = normalize(mul(input.Normal, WorldInverseTranspose)); // �@��
    float3 lightDir = normalize(lightPos - input.WorldPosition); // ��������
    float3 viewDir = normalize(cameraPos - input.WorldPosition); // ��������
    float3 halfDir = normalize(lightDir + viewDir); // �n�[�t�x�N�g��

    // �g�U���ː����̌v�Z
    float diffuseTerm = diffuseCoefficient * max(dot(normal, lightDir), 0.0f);

    // ���ʔ��ː����̌v�Z
    float D = NormalDistributionFunction(dot(normal, halfDir)); // �@�����z�֐�
    float G = GeometricAttenuationCoefficient(normal, viewDir, halfDir, lightDir); // �􉽌�����
    float F = FresnelReflectionCoefficient(dot(normal, lightDir), refractiveIndex); // �t���l�����ˌW��

    // ���ʔ��˂̍ŏI��
    float specularTerm = specularCoefficient * D * F * G /
                         (4 * dot(normal, lightDir) * dot(normal, viewDir) + 1e-7);

    // �������܂߂��ŏI�I�ȐF���v�Z
    float4 finalColor = diffuseTerm * diffuseColor + specularTerm * specularColor + ambientCoefficient * diffuseColor;
    
    return finalColor;
}
