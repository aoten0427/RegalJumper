// ================================================================ 
// ファイル名 : SelectArrow.cpp
// 作成者 : 景山碧天
// 説明 :  ステージ選択矢印
// ================================================================
#include"pch.h"
#include"SelectArrow.h"
#include"Base/Scene/Scene.h"
#include"Game/GameManager.h"
#include"Base/Event/Subject.h"
#include"Base/Event/Observer.h"
#include"Base/Tween/DoTween.h"
#include"Base/Sound/Sound.h"

constexpr float POSITION_Y = 130;
constexpr float NOMAL_X = 1110;
constexpr float INVERSION_X = 810;
constexpr float MOVEING = 10;
constexpr float MOVE_SPEED = 1.2f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
/// <param name="inversion">反転フラグ</param>
SelectArrow::SelectArrow(Canvas* canvas,bool inversion):Button(canvas,"Arrow",2)
	,
	m_inversion{inversion},
	m_position{},
	m_selectSubject{nullptr},
	m_observer{nullptr}
{
	using namespace DirectX::SimpleMath;
	//サイズ設定
	SetSize(Vector2(45, 45));

	Tween* tween = AddComponent<Tween>(this,true);
	//向きによる初期設定
	if (inversion)
	{
		//向き反転
		SetSize(GetSize() * -1);
		m_position = Vector2(INVERSION_X, POSITION_Y);
		//移動Tween作成
		tween->DoVector2(m_position, Vector2(INVERSION_X - MOVEING, POSITION_Y), MOVE_SPEED).
			SetLoop(-1).SetEase(Easing::Ease::InOutQuad);
		//通知作成
		m_selectSubject = AddComponent<Subject<>>(this, "LeftArrow");
	}
	else
	{
		m_position = Vector2(NOMAL_X, POSITION_Y);
		//移動Tween作成
		tween->DoVector2(m_position, Vector2(NOMAL_X + MOVEING, POSITION_Y), MOVE_SPEED).
			SetLoop(-1).SetEase(Easing::Ease::InOutQuad);
		//通知作成
		m_selectSubject = AddComponent<Subject<>>(this, "RightArrow");
	}

	//オブザーバー作成
	m_observer = AddComponent<Observer<>>(this);
	m_observer->SetFunction([&]() {CheckView(); });
	m_observer->RegistrationSubject("LeftArrow");
	m_observer->RegistrationSubject("RightArrow");

	//サウンド作成
	m_sound = AddComponent<Sound>(this, Sound::SoundType::SE, "Select3", false);

	//表示判断
	CheckView();
}

/// <summary>
/// 位置を更新
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void SelectArrow::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	SetPosition(m_position);
}

/// <summary>
/// マウス感知イベント
/// </summary>
/// <param name="within">範囲内か</param>
void SelectArrow::MouseWithinEvent(bool within)
{
	//色変更
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (within)
	{
		SetColor(DirectX::SimpleMath::Vector4(0.33, 1, 0.8, 1.0f));
	}
	else
	{
		SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}

/// <summary>
/// 左マウスクリックイベント
/// </summary>
/// <param name="within">範囲内か</param>
void SelectArrow::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::PLAY)return;
	if (!GetActive())return;
	if (!within)return;
	m_sound->Play();
	if (m_inversion)
	{
		//ステージ番号を1減らす
		if (GameManager::GetInstance()->ChangeStage(-1))
		{
			//通知
			m_selectSubject->Notify();
		}
	}
	else
	{
		//ステージ番号を1増やす
		if (GameManager::GetInstance()->ChangeStage(1))
		{
			//通知
			m_selectSubject->Notify();
		}
	}
}

/// <summary>
/// 表示判断
/// </summary>
void SelectArrow::CheckView()
{
	SetActive(true);
	std::pair<int, int> stageNum = GameManager::GetInstance()->GetStageNum();

	if (m_inversion)
	{
		//最低ステージなら描画しない
		if (stageNum.first * 10 + stageNum.second == 11)SetActive(false);
	}
	else
	{
		//最高ステージなら描画しない
		if (stageNum.first * 10 + stageNum.second >=
			GameManager::GetInstance()->MAX_STAGE_MAIN * 10 + GameManager::GetInstance()->MAX_STAGE_SUB)
			SetActive(false);
	}
}
