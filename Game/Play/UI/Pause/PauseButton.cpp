// ================================================================ 
// ファイル名 : PauseButton.h
// 作成者 : 景山碧天
// 説明 :  ポーズで扱うボタン
// ================================================================
#include"pch.h"
#include"PauseButton.h"
#include"Base/Screen.h"
#include"Base/Scene/Scene.h"

constexpr DirectX::SimpleMath::Vector2 BUTTON_SIZE = DirectX::SimpleMath::Vector2(400, 80);
constexpr int BEGIN = 240;
constexpr int HEIGHT = 100;//高さ
constexpr int RESTART_Y = 240;//リスタート位置
constexpr int RESTART_WIDTH = 400;//リスタート幅
constexpr int STAGE_SELECT_Y = 340;//ステージセレクト位置
constexpr int STAGE_SELECT_WIDTH = 400;//ステージセレクト幅
constexpr int OPTION_Y = 440;//オプション位置
constexpr int OPTION_WIDTH = 400;//オプション幅

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
/// <param name="type">ボタンの種類</param>
PauseButton::PauseButton(Canvas* canvas, TYPE type):Button(canvas)
{
	SetRenderOrder(3);
	SetData(type);
}

/// <summary>
/// マウス感知イベント
/// </summary>
/// <param name="within">範囲内か</param>
void PauseButton::MouseWithinEvent(bool within)
{
	//色変更
	if (within)
	{
		SetColor(DirectX::SimpleMath::Vector4(0, 0.87f, 0.82f, 1));
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
void PauseButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::STOP)return;
	if (within)DoFunction();
}

/// <summary>
/// 選択肢によってデータを設定
/// </summary>
/// <param name="type"></param>
void PauseButton::SetData(TYPE type)
{
	//画像，位置、大きさを設定
	DirectX::SimpleMath::Vector2 position(Screen::CENTER_X, 0);
	DirectX::SimpleMath::Vector2 size(BUTTON_SIZE);
	switch (type)
	{
	case PauseButton::TYPE::RESTART:
		SetTexture("ReStartButton");
		position.y = BEGIN;
		break;
	case PauseButton::TYPE::STAGESELECT:
		SetTexture("StageSelectButton");
		position.y = BEGIN + HEIGHT;
		break;
	case PauseButton::TYPE::OPTION:
		SetTexture("OptionButton");
		position.y = BEGIN + HEIGHT * 2;
		break;
	case PauseButton::TYPE::QUIT:
		SetTexture("QuitP");
		position.y = BEGIN + HEIGHT * 3;
	default:
		break;
	}
	SetPosition(position);
	SetSize(size);
}
