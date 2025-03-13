// ================================================================ 
// ファイル名 : SelectObjects.cpp
// 作成者 : 景山碧天
// 説明 :  セレクトシーンでのオブジェクト
// ================================================================
#include"pch.h"
#include"SelectObjects.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Scene/Scene.h"
#include"Base/Event/Observer.h"
#include"Game/Play/Stage/Skydome.h"
#include"Game/Play/Stage/Box.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
SelectObjects::SelectObjects(Scene* scene):Object(scene)
{
	using namespace DirectX::SimpleMath;
	//プレイシーン遷移オブザーバ作成
	m_toPlayObserver = AddComponent<Observer<>>(this);
	m_toPlayObserver->SetFunction([&]() {ToPlay(); });
	m_toPlayObserver->RegistrationSubject("SelectPlay");

	//スカイドーム生成
	Skydome* dome = scene->AddObject<Skydome>(scene);
	dome->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0.1f));
	//プレイヤー生成
	m_model = scene->AddObject<SpiderModels>(scene);
	m_model->GetTransform()->SetPosition(Vector3(2.8f, -0.5f, 11));
	m_model->GetTransform()->TransRotate(Vector3::UnitY, -5);
	//ブロック生成
	Box* box = scene->AddObject<Box>(scene);
	box->GetTransform()->SetPosition(Vector3(0, -7.5f, 0));
	box->GetTransform()->SetScale(Vector3(20.0f, 5.0f, 20.0f));
}

/// <summary>
/// プレイシーン遷移処理
/// </summary>
void SelectObjects::ToPlay()
{
	m_model->ChangeState(SpiderModelState::RenderType::EXIT);
}
