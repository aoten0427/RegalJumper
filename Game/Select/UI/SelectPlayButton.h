// ================================================================ 
// ファイル名 : SelectPlayButton.h
// 作成者 : 景山碧天
// 説明 :  プレイシーン移行ボタン
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

template<typename...Args>
class Subject;

class SelectPlayButton :public Button
{
private:
	//色変更UI
	UserInterface* m_bg;
	//クリック時通知
	Subject<>* m_ClickSubject;
public:
	//コンストラクタ
	SelectPlayButton(Canvas* canvas);
	//デストラクタ
	~SelectPlayButton()override = default;
	//マウス感知イベント
	void MouseWithinEvent(bool within);
	//左クリックイベント
	void LeftClickEvent(bool within);
};