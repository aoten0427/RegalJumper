// ================================================================ 
// ファイル名 : Pause.cpp
// 作成者 : 景山碧天
// 説明 :  プレイ画面ポーズ
// ================================================================
#include"pch.h"
#include"Pause.h"
#include"Base/Base.h"
#include"Base/Screen.h"
#include"Base/Event/Subject.h"
#include"Base/Event/Observer.h"
#include"Base/Fade/FadeManager.h"
#include"Game/GameManager.h"
#include"Game/Play/UI/Pause/PauseButton.h"
#include"Game/Play/UI/Pause/PauseExitButton.h"
#include"Game/Play/UI/Pause/QuitPage.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
Pause::Pause(Canvas* canvas):UserInterface(canvas)
	,
	m_isOpen{false},
	m_UIBase{nullptr},
	m_base{nullptr},
	m_openSubject{nullptr},
	m_closeSubject{nullptr},
	m_oldSceneState{Scene::State::PLAY}
{
	using namespace DirectX::SimpleMath;
	
	//白背景
	SetSize(Vector2(Screen::WIDTH, Screen::HEIGHT));
	SetColor(Vector4(1, 1, 1, 0.5));
	m_UIBase = GetScene()->AddObject<Object>(GetScene());
	m_UIBase->GetTransform()->SetParent(GetTransform());

	//ベース作成
	m_base = GetScene()->AddObject<UserInterface>(canvas, "Pause", 1);
	m_base->SetSize(Vector2(640, 640));
	m_base->GetTransform()->SetParent(m_UIBase->GetTransform());

	//退出ページ作成
	m_quitPage = GetScene()->AddObject<QuitPage>(canvas, this);

	PauseButton* quitButton = GetScene()->AddObject<PauseButton>(canvas, PauseButton::TYPE::QUIT);
	quitButton->GetTransform()->SetParent(m_UIBase->GetTransform());
	quitButton->SetFunction([&]() {
		m_quitPage->SetActive(true);
		SetActive(false);
		});

	//各ボタン作成
	//リスタートボタン
	PauseButton* reStartButton = GetScene()->AddObject<PauseButton>(canvas, PauseButton::TYPE::RESTART);
	reStartButton->GetTransform()->SetParent(m_UIBase->GetTransform());
	reStartButton->SetFunction([&]() {
		//プレイシーンへの移行をセット
		FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
			GetScene()->ChangeScene(Scene::SceneID::PLAY);
			});
		});

	//ステージセレクトボタン
	PauseButton* stageSelectButton = GetScene()->AddObject<PauseButton>(canvas, PauseButton::TYPE::STAGESELECT);
	stageSelectButton->GetTransform()->SetParent(m_UIBase->GetTransform());
	stageSelectButton->SetFunction([&]() {
		//セレクトシーンへの移行をセット
		FadeManager::GetInstance()->FadeStart("NormalFade", [&]() {
			GetScene()->ChangeScene(Scene::SceneID::SELECT);
			});
		});

	//オプションボタン
	PauseButton* optionButton = GetScene()->AddObject<PauseButton>(canvas, PauseButton::TYPE::OPTION);
	optionButton->GetTransform()->SetParent(m_UIBase->GetTransform());
	optionButton->SetFunction([&]() {
		//オプションを開く
		GameManager::GetInstance()->OpenOption();
		m_UIBase->SetActive(false);
		});

	

	//退出ボタン作成
	PauseExitButton* exitButton = GetScene()->AddObject<PauseExitButton>(canvas);
	exitButton->GetTransform()->SetParent(m_UIBase->GetTransform());
	exitButton->SetFunction([&]() {Close(); });
	


	//サブジェクト作成
	m_openSubject = AddComponent<Subject<>>(this, "PauseOpen");
	m_closeSubject = AddComponent<Subject<>>(this, "PauseClose");
	//オプションボタン不随オブザーバー作成
	Observer<>* optionClose = AddComponent<Observer<>>(this);
	optionClose->SetFunction([&]() {m_UIBase->SetActive(true); });
	optionClose->RegistrationSubject("OptionClose");

	//見えなくする
	SetActive(false);
}

/// <summary>
/// アップデート 開くかを判断
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Pause::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	Open();
}

/// <summary>
/// 開く
/// </summary>
void Pause::Open()
{
	if (m_isOpen)return;
	//エスケープ押し判断
	if (!GetCommonResources()->GetInput()->IsKeyPress(DirectX::Keyboard::Escape))return;
	//シーンが準備状態かプレイ状態か
	if (GetScene()->GetState() == Scene::State::RESERVE || GetScene()->GetState() == Scene::State::PLAY)
	{
		m_isOpen = true;
		//見えるようにする
		SetActive(true);
		//ストップ状態に変更
		GetScene()->ChangeState(Scene::State::STOP);
		//サブジェクト実行
		m_openSubject->Notify();
		//状態を記録
		m_oldSceneState = GetScene()->GetState();
		//カーソルをオンにする
		GameManager::GetInstance()->ViewCursor(true);
	}
}

/// <summary>
/// 閉じる
/// </summary>
void Pause::Close()
{
	m_isOpen = false;
	//見えなくする
	SetActive(false);
	//サブジェクト実行
	m_closeSubject->Notify();
	//シーンの状態を戻す
	GetScene()->ChangeState(m_oldSceneState);
	//カーソルをオフにする
	GameManager::GetInstance()->ViewCursor(false);
}
