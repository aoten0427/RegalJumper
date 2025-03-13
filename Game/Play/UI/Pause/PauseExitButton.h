// ================================================================ 
// ファイル名 : PauseExitButton.h
// 作成者 : 景山碧天
// 説明 :  ポーズ退出ボタン
// ================================================================

#pragma once
#include"Base/Canvas//UserInterface/Button.h"

class PauseExitButton :public Button
{
private:
public:
	//コンストラクタ
	PauseExitButton(Canvas* canvas);
	//デストラクタ
	~PauseExitButton()override = default;

	//マウス感知イベント
	void MouseWithinEvent(bool within) override;
	//左クリックイベント
	void LeftClickEvent(bool within) override;
};