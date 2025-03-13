// ================================================================ 
// ファイル名 : PauseExitButton.cpp
// 作成者 : 景山碧天
// 説明 :  ポーズ退出ボタン
// ================================================================
#include"pch.h"
#include"PauseExitButton.h"
#include"Base/Scene/Scene.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
PauseExitButton::PauseExitButton(Canvas* canvas):Button(canvas,"Exit",3)
{
	SetSize(DirectX::SimpleMath::Vector2(50, 50));
	SetPosition(DirectX::SimpleMath::Vector2(870, 570));
}

/// <summary>
/// マウス感知イベント
/// </summary>
/// <param name="within">範囲内か</param>
void PauseExitButton::MouseWithinEvent(bool within)
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
void PauseExitButton::LeftClickEvent(bool within)
{
	if (GetScene()->GetState() != Scene::State::STOP)return;
	//ポーズを閉じる
	if (within)DoFunction();
}
