#include "Base/Shader/Model.hlsli"



cbuffer ConstantBuffer : register(b1)
{
    float4 lightPosition;        // 光源の位置 (ワールド座標)
    float4 cameraPosition;       // カメラの位置 (ワールド座標)
    float diffuseCoefficient;    // 拡散反射係数
    float ambientCoefficient;    // 環境光係数
    float specularCoefficient;   // 鏡面反射係数
    float roughness;             // 粗さ
    float4 diffuseColor;         // 拡散反射の色
    float4 specularColor;        // 鏡面反射の色
    float refractiveIndex;       // 屈折率
    float3 reserved;             // 予備の値
}

// 粗さによるハイライトを計算
float NormalDistributionFunction(float cosTheta)
{
    float alpha = roughness * roughness;
    float alpha2 = alpha * alpha;
    float cosTheta2 = cosTheta * cosTheta;

    float denominator = cosTheta2 * (alpha2 - 1.0) + 1.0;
    return alpha2 / (3.14159 * denominator * denominator);
}


// 幾何減衰項を計算
float SmithG(float cosTheta, float roughness)
{
    float alpha = roughness * roughness;
    float tanTheta = sqrt(1.0 - cosTheta * cosTheta) / cosTheta;
    float a = 1.0 / (alpha * tanTheta);
    return a < 1.6 ? (3.535 * a + 2.181 * a * a) / (1.0 + 2.276 * a + 2.577 * a * a) : 1.0;
}


// 幾何減衰係数を計算
float GeometricAttenuationCoefficient(float3 normal, float3 viewDir, float3 halfDir, float3 lightDir)
{
    float Gv = SmithG(dot(normal, viewDir), roughness);
    float Gl = SmithG(dot(normal, lightDir), roughness);
    return Gv * Gl;
}


// フレネル反射係数を計算
float FresnelReflectionCoefficient(float cosTheta, float eta)
{
    float c = abs(cosTheta);
    float g = sqrt(eta * eta + c * c - 1);
    float gMinusC = g - c;
    float gPlusC = g + c;
    return 0.5f * (gMinusC * gMinusC / (gPlusC * gPlusC)) *
           (1 + pow((c * gPlusC - 1) / (c * gMinusC + 1), 2));
}


// クックトレンスモデル
float4 CookTorrance(PS_INPUT input)
{
    // 光源とカメラの位置を取得
    float3 lightPos = lightPosition.xyz;
    float3 cameraPos = cameraPosition.xyz;

    // 法線、光線、視線、ハーフベクトルを計算
    float3 normal = normalize(mul(input.Normal, WorldInverseTranspose)); // 法線
    float3 lightDir = normalize(lightPos - input.WorldPosition); // 光線方向
    float3 viewDir = normalize(cameraPos - input.WorldPosition); // 視線方向
    float3 halfDir = normalize(lightDir + viewDir); // ハーフベクトル

    // 拡散反射成分の計算
    float diffuseTerm = diffuseCoefficient * max(dot(normal, lightDir), 0.0f);

    // 鏡面反射成分の計算
    float D = NormalDistributionFunction(dot(normal, halfDir)); // 法線分布関数
    float G = GeometricAttenuationCoefficient(normal, viewDir, halfDir, lightDir); // 幾何減衰項
    float F = FresnelReflectionCoefficient(dot(normal, lightDir), refractiveIndex); // フレネル反射係数

    // 鏡面反射の最終項
    float specularTerm = specularCoefficient * D * F * G /
                         (4 * dot(normal, lightDir) * dot(normal, viewDir) + 1e-7);

    // 環境光を含めた最終的な色を計算
    float4 finalColor = diffuseTerm * diffuseColor + specularTerm * specularColor + ambientCoefficient * diffuseColor;
    
    return finalColor;
}
