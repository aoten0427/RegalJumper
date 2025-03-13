// ================================================================ 
// ファイル名 : PlayCanvas.cpp
// 作成者 : 景山碧天
// 説明 :  プレイシーンキャンバス
// ================================================================
#include"pch.h"
#include"PlayCanvas.h"
#include"Base/Scene/Scene.h"
#include"Base/Event/Observer.h"
#include"Base/Object/UnbreakableManager.h"
#include"Game/GameManager.h"
#include"Game/Play/UI/Time.h"
#include"Game/Play/UI/UIReticle.h"
#include"Game/Play/UI/Pause/Pause.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
PlayCanvas::PlayCanvas(Scene* scene):GameCanvas(scene)
	,
	m_gameTimer{},
	m_time{nullptr}
{
	//タイマー作成
	m_time = scene->AddObject<Time>(this);
	m_time->SetStartX(520);
	m_time->SetPositionY(50);
	m_time->SetSize(DirectX::SimpleMath::Vector2(40, 70));
	//レティクル範囲作成
	scene->AddObject<UIReticle>(this);
	//ポーズ作成
	scene->AddObject<Pause>(this);

	//終了オブザーバー作成
	m_finishObserver = AddComponent<Observer<>>(this);
	m_finishObserver->SetFunction([&]() {
		GameManager::GetInstance()->SetResultTimer(m_gameTimer);
		});
	m_finishObserver->RegistrationSubject("SpiderExit");
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void PlayCanvas::ObjectUpdate(float deltatime)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	//プレイ時間更新
	m_gameTimer += deltatime;
	m_time->SetCount(m_gameTimer);
}
