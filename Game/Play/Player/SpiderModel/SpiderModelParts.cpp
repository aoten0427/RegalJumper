// ================================================================ 
// ファイル名 : SpiderModelParts.cpp
// 作成者 : 景山碧天
// 説明 :  スパイダーモデルの各パーツ
// ================================================================
#include"pch.h"
#include"SpiderModelParts.h"
#include"Base/Resource/GameResources.h"
#include"Base/Base.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
/// <param name="name">パーツ名</param>
/// <param name="modelname">読み込みモデル名</param>
/// <param name="texturename">読み込み画像名</param>
SpiderModelParts::SpiderModelParts(Scene* scene, std::string name, std::string modelname, std::string texturename):Object(scene)
	,
	m_name{name}
{
	m_model = AddComponent<Model3D>(this, modelname);
	m_model->SetActive(false);
	//モデル画像ロード
	m_modelTexture = GameResources::GetInstance()->GetTexture(texturename);
}



