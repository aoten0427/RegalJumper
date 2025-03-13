// ================================================================ 
// ファイル名 : PlayFade.cpp
// 作成者 : 景山碧天
// 説明 :  プレイシーンリセット用フェード
// ================================================================
#include"pch.h"
#include"PlayFade.h"
#include"Base/Screen.h"
#include"Base/Scene/Scene.h"
#include"Base/Tween/DoTween.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
PlayFade::PlayFade(Canvas* canvas):Fade(canvas,"PlayFade")
	,
	m_position{ Screen::WIDTH * 2, Screen::CENTER_Y },
	m_closeFunction{ nullptr }
{

	using namespace DirectX::SimpleMath;
	//基本情報設定
	SetPosition(m_position);
	SetSize(Vector2(Screen::WIDTH * 2, Screen::HEIGHT));
	SetColor(Vector4(0, 0, 0, 1));

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
			});
	m_sequence->Pause();
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void PlayFade::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	//ポジションをセット
	SetPosition(m_position);
}

/// <summary>
/// フェードスタート
/// </summary>
/// <param name="function">実行イベント</param>
void PlayFade::Start(std::function<void()> function)
{
	//フェードイン状態に変更
	SetState(Fade::State::DoIn);
	//処理を設定
	m_closeFunction = function;
	//Sequenceを開始
	m_sequence->Play();
}
