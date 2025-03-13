// ================================================================ 
// ファイル名 : PlayButton.h
// 作成者 : 景山碧天
// 説明 :  タイトル画面でのプレイボタン
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class Sound;

class PlayButton :public Button
{
private:
	Sound* m_sound;
public:
	//コンストラクタ
	PlayButton(Canvas* canvas);
	//デストラクタ
	~PlayButton() override = default;
	//マウス感知イベント
	void MouseWithinEvent(bool within) override;
	//左マウスクリックイベント
	void LeftClickEvent(bool within) override;
};
