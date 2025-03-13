// ================================================================ 
// ファイル名 : PlayCenter.cpp
// 作成者 : 景山碧天
// 説明 :  プレイシーンの管理
// ================================================================

#include"pch.h"
#include"PlayCenter.h"
#include"Base/Scene/Scene.h"
#include"Base/Event/Observer.h"
#include"Base/Event/Subject.h"
#include"Base/Fade/FadeManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
PlayCenter::PlayCenter(Scene* scene) :Object(scene)
{
	//リセット呼び出しオブザーバー作成
	m_resetObserver = AddComponent<Observer<>>(this);
	m_resetObserver->SetFunction([&]() {Reset(); });
	m_resetObserver->RegistrationSubject("PlayerDeath");

	//リセット用サブジェクト作成
	m_resetSubject = AddComponent<Subject<>>(this, "PlayReset");

	//リザルトシーン遷移オブザーバ作成
	m_exitObserver = AddComponent<Observer<>>(this);
	m_exitObserver->SetFunction([&]() {ToResult(); });
	m_exitObserver->RegistrationSubject("SpiderExit");
}

/// <summary>
/// プレイシーンリセット処理
/// </summary>
void PlayCenter::Reset()
{
	FadeManager::GetInstance()->FadeStart("PlayFade", [&]() {
		m_resetSubject->Notify();
		});
}

/// <summary>
/// リザルトシーン遷移処理
/// </summary>
void PlayCenter::ToResult()
{
	FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
		GetScene()->ChangeScene(Scene::SceneID::RESULT);
		});
}