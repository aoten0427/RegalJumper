// ================================================================ 
// ファイル名 : SelectCenter.cpp
// 作成者 : 景山碧天
// 説明 :  セレクトシーンを管理
// ================================================================
#include"pch.h"
#include"SelectCenter.h"
#include"Base/Fade/FadeManager.h"
#include"Base/Scene/Scene.h"
#include"Base/Event/Observer.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
SelectCenter::SelectCenter(Scene* scene):Object(scene)
{
	//開始オブザーバー作成
	m_begin = AddComponent<Observer<>>(this);
	m_begin->SetFunction([&]() {GetScene()->ChangeState(Scene::State::PLAY); });
	m_begin->RegistrationSubject("Reserve");

	//終了オブザーバー作成
	m_finish = AddComponent<Observer<>>(this);
	m_finish->SetFunction([&]() {
		FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
			GetScene()->ChangeScene(Scene::SceneID::PLAY);
			});
		});
	m_finish->RegistrationSubject("SpiderExit");
}
