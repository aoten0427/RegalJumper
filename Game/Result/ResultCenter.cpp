// ================================================================ 
// ファイル名 : ResultCenter.cpp
// 作成者 : 景山碧天
// 説明 :  リザルトシーンの管理
// ================================================================
#include"pch.h"
#include"ResultCenter.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonResources.h"
#include"Base/Input/DirectXInputs.h"
#include"Base/Event/Observer.h"
#include"Base/Event/Subject.h"
#include"Base/Fade/FadeManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
ResultCenter::ResultCenter(Scene* scene):Object(scene)
{
	//プレイ状態への遷移オブザーバ-
	m_beginObserver = AddComponent<Observer<>>(this);
	m_beginObserver->SetFunction([&]() {GetScene()->ChangeState(Scene::State::PLAY); });
	m_beginObserver->RegistrationSubject("Reserve");
	//リザルト処理のスキップサブジェクト
	m_skipSubject = AddComponent<Subject<>>(this, "ResultSkip");

	GetScene()->ChangeState(Scene::State::PLAY);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void ResultCenter::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	//左マウスクリック
	if (GetCommonResources()->GetInput()->GetMouseTracker()->leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//プレイ状態の場合スキップ処理
		if (GetScene()->GetState() == Scene::State::PLAY)
		{
			m_skipSubject->Notify();
			GetScene()->ChangeState(Scene::State::END);
		}
		//終了状態の場合セレクトシーンへ遷移
		else if (GetScene()->GetState() == Scene::State::END)
		{
			FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
				GetScene()->ChangeScene(Scene::SceneID::SELECT);
				});
		}
	}
}
