// ================================================================ 
// ファイル名 : OptionExitButton.h
// 作成者 : 景山碧天
// 説明 :  オプション退出ボタン
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class Option;

class OptionExit :public Button
{
private:
public:
	//コンストラクタ
	OptionExit(Canvas* canvas,Option* option);
	//デストラクタ
	~OptionExit() override = default;
	//マウス感知イベント
	void MouseWithinEvent(bool within)override;
};
