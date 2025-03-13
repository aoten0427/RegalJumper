// ================================================================ 
// ファイル名 : SelectExitButton.h
// 作成者 : 景山碧天
// 説明 :  セレクトシーン退出ボタン
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class SelectExitButton :public Button
{
private:
	UserInterface* m_str;
public:
	//コンストラクタ
	SelectExitButton(Canvas* canvas);
	//デストラクタ
	~SelectExitButton()override = default;
	//マウス感知イベント
	void MouseWithinEvent(bool within);
	//左クリックイベント
	void LeftClickEvent(bool within);
};