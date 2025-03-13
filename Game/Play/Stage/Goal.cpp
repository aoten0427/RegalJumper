// ================================================================ 
// ファイル名 : Goal.cpp
// 作成者 : 景山碧天
// 説明 :  ゴール
// ================================================================
#include"pch.h"
#include"Goal.h"
#include"Base/Base.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
Goal::Goal(Scene* scene):Object(scene)
{
	using namespace DirectX::SimpleMath;

	//モデル生成
	auto model = AddComponent<Model3D>(this,"Goal");
	model->SetPosition(Vector3(0, 0.02f, 0));
	model->SetScale(Vector3(24.0f, 24.0f, 24.0f));
	//コライダー生成
	AddComponent<Sphere>(this, CollisionType::TRIGGER, nullptr, false,2.0f);
}
