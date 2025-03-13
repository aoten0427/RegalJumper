// ================================================================ 
// ファイル名 : Button.cpp
// 作成者 : 景山碧天
// 説明 :  ボタン基底クラス
// ================================================================

#include"pch.h"
#include"Button.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
/// <param name="filename">読み込み画像</param>
/// <param name="renderorder">優先度</param>
Button::Button(Canvas* canvas, std::string filename, int renderorder):UserInterface(canvas,filename,renderorder)
	,
	m_function{nullptr}
{
	//マウスイベントをオンに
	SetMouseEventFlag(true);
}

/// <summary>
/// 関数実行
/// </summary>
void Button::DoFunction()
{
	if (m_function)m_function();
}

/// <summary>
/// 左マウスクリックイベント
/// </summary>
/// <param name="within">内部判定</param>
void Button::LeftClickEvent(bool within)
{
	if (!within)return;
	DoFunction();
}
