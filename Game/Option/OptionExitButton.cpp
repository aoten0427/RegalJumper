// ================================================================ 
// ファイル名 : OptionExitButton.cpp
// 作成者 : 景山碧天
// 説明 :  オプション退出ボタン
// ================================================================
#include"pch.h"
#include"OptionExitButton.h"
#include"Base/Base.h"
#include"Game/Option/Option.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">キャンバス</param>
/// <param name="option">オプション</param>
OptionExit::OptionExit(Canvas* canvas,Option* option):Button(canvas,"Exit",6)
{
	////親を設定
	GetTransform()->SetParent(option->GetTransform());
	//サイズ設定
	SetSize(DirectX::SimpleMath::Vector2(60, 60));
	//位置設定
	SetPosition(DirectX::SimpleMath::Vector2(830, 600));
	
	SetActive(false);
}

/// <summary>
/// マウス感知イベント
/// </summary>
/// <param name="within">自身の範囲内か</param>
void OptionExit::MouseWithinEvent(bool within)
{
	//色変更
	if (within)
	{
		SetColor(DirectX::SimpleMath::Vector4(0.1, 0.75f, 0.93f, 1));
	}
	else
	{
		SetColor(DirectX::SimpleMath::Vector4(1, 1, 1, 1));
	}
}


