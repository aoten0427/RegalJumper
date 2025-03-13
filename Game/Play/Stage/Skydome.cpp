// ================================================================ 
// ファイル名 : Skydome.h
// 作成者 : 景山碧天
// 説明 :  天球
// ================================================================

#include"pch.h"
#include"Skydome.h"
#include"Base/Component/Render/Model3D.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
Skydome::Skydome(Scene* scene):Object(scene)
{
	Model3D* model = AddComponent<Model3D>(this, "Skydome");
	using namespace DirectX;
	model->GetModel()->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ベーシックエフェクトを設定する
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				//ライト無効か
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);


				// モデルを自発光させる
				basicEffect->SetEmissiveColor(XMVECTOR{ 0.5f,0.5f,0.5f,1 });
			}
		}
	);
	model->SetScale(SimpleMath::Vector3(30.0f, 30.0f, 30.0f));
	model->SetPosition(SimpleMath::Vector3(0, 0, -1000));
	model->SetIsShadow(false);

}
