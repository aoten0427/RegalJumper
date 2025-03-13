// ================================================================ 
// ファイル名 : GameFade.cpp
// 作成者 : 景山碧天
// 説明 :  ゲームの基本フェード
// ================================================================
#include"pch.h"
#include"GameFade.h"
#include"Base/Screen.h"
#include"Base/Scene/Scene.h"
#include"Base/Tween/Sequence.h"
#include"Base/Tween/TweenCore.h"
#include"Base/Event/Subject.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
GameFade::GameFade(Canvas* canvas):Fade(canvas,"NormalFade")
	,
	m_position{ Screen::WIDTH * 2, Screen::CENTER_Y },
	m_closeFunction{nullptr}
{
	GetScene()->ChangeState(Scene::State::RESERVE);

	using namespace DirectX::SimpleMath;
	//基本情報設定
	SetPosition(m_position);
	SetSize(Vector2(Screen::WIDTH * 2, Screen::HEIGHT));
	SetColor(Vector4(0, 0, 0, 1));
	SetTexture("Fade1");

	m_sequence = AddComponent<Sequence>(this);
	//フェードイン処理作成
	m_sequence->AppendVector2(m_position, Vector2(Screen::CENTER_X, Screen::CENTER_Y), 0.7f).SetCompleteFunction([&]() {
		if (m_closeFunction)m_closeFunction();
		SetState(Fade::State::In);
		});
	//クローズ処理作成
	m_sequence->AppendVector2(m_position, Vector2(Screen::CENTER_X, Screen::CENTER_Y), 0.1f).SetChangeType(TweenCore::ChangeType::ReLoad).
			SetCompleteFunction([&]() {
			SetState(Fade::State::DoOut);
			GetScene()->ChangeState(Scene::State::FEAD);
		});
	//フェードアウト処理作成
	m_sequence->AppendVector2(m_position, Vector2(-Screen::WIDTH, Screen::CENTER_Y), 0.7f).SetChangeType(TweenCore::ChangeType::ReLoad).
			SetCompleteFunction([&]() {
			SetState(Fade::State::Out);
			//ポジションリセット
			m_position = Vector2(Screen::WIDTH * 2, Screen::CENTER_Y);
			//シーケンスを初期状態に
			m_sequence->ReStart();
			m_sequence->Pause();
			GetScene()->ChangeState(Scene::State::RESERVE);
		});
	m_sequence->Pause();

	m_finishSubject = AddComponent<Subject<>>(this, "GameFade");
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void GameFade::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	//ポジションをセット
	SetPosition(m_position);
}

/// <summary>
/// フェード開始
/// </summary>
/// <param name="function">クローズ時の処理</param>
void GameFade::Start(std::function<void()> function)
{
	//シーンをフェード状態に
	GetScene()->ChangeState(Scene::State::FEAD);
	//フェードイン状態に変更
	SetState(Fade::State::DoIn);
	//処理を設定
	m_closeFunction = function;
	//Sequenceを開始
	m_sequence->Play();
}


