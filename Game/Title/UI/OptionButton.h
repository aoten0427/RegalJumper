// ================================================================ 
// ファイル名 : OptionButton.h
// 作成者 : 景山碧天
// 説明 :  タイトル画面でのオプションボタン
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class Sound;

class OptionButton :public Button
{
private:
	Sound* m_sound;
public:
	//コンストラクタ
	OptionButton(Canvas* canvas);
	//デストラクタ
	~OptionButton() override = default;
	//マウス感知イベント
	void MouseWithinEvent(bool within);
	//左マウスクリックイベント
	void LeftClickEvent(bool within);
};