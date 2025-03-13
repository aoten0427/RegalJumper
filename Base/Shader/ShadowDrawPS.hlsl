/*
	ライトwithシャドウマップ用ピクセルシェーダ
*/
#include"Model.hlsli"
#include"TestShadow.hlsli"

Texture2D<float4> Texture : register(t0);
sampler Sampler : register(s0);




float4 main(PS_SMD_INPUT input) : SV_TARGET0
{
    // 法線を正規化する
    float3 normal = normalize(input.NormalWS);
    /*
        ・負荷を下げるなら、頂点シェーダで計算する
        ・精度をあげるなら、ピクセルシェーダで計算する
    */

    
    

    // ----------------------------------------------------------- //
    // ディフューズ
    // ----------------------------------------------------------- //
 
	/* 手順９ */

    // ライトを照らす方向を計算する
    //float3 lightDir = normalize(input.PositionWS.xyz - lightPosition.xyz);
    float3 lightDir = normalize(lightDirirection);
    
    // ライトへ向かうベクトル
    float3 toLight = (-lightDir);

    // 光の強さを内積から算出する
    float intensity1 = max(dot(normal, toLight), 0.0f);

    float shadow = ShadowMap(input);

    // ライトと影による明るさを計算する
    //float3 lightAmount = shadow * (1.0f - lightAmbient) + lightAmbient;
    float3 lightAmount = lerp(lightAmbient, float3(1.0f, 1.0f, 1.0f), shadow);
    lightAmount *= intensity1;

    // 拡散反射色を求める 
    float3 diffuse = DiffuseColor.rgb * lightAmount;

        
    // ----------------------------------------------------------- //
    // スペキュラ
    // ----------------------------------------------------------- //
    
	/* 手順１０ */
    
    // 視線ベクトル
    float3 toEye = normalize(EyePosition - input.PositionWS.xyz);

    // ハーフベクトル＝カメラ座標＋ライト座標
    float3 halfVector = normalize(toEye + toLight);

    // 鏡面反射の影響割合を内積を使い計算する
    float intensity2 = max(dot(normal, halfVector), 0.0f);

    // スペキュラパワーを指数として使いハイライトのかかり具合を調整する
    float3 specular = pow(intensity2, SpecularPower) * SpecularColor;
    
    // 影の影響を考慮する
    specular *= shadow;
 
    
    // ----------------------------------------------------------- //
    // 最終カラー
    // ----------------------------------------------------------- //

    // テクスチャカラーをサンプルする
    float4 textureColor = /*Texture.Sample(Sampler, input.TexCoord)*/float4(1,1,1,1);
    
    // テクスチャの色に拡散反射と鏡面反射を反映する
    float3 finalColor = textureColor.rgb * diffuse + specular + lightAmbient;
    
    return float4(shadow, shadow, shadow, 1);
    
    return float4(finalColor, 1.0f);
}
