// ================================================================ 
// ファイル名 : QuitPage.h
// 作成者 : 景山碧天
// 説明 :  退出ページ
// ================================================================
#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"
#include"Base/Canvas/UserInterface/Button.h"

class Pause;

class QButton :public Button
{
public:
	QButton(Canvas* canvas);

	//マウス感知イベント
	void MouseWithinEvent(bool within) override;
};

class QuitPage :public UserInterface
{
private:
public:
	QuitPage(Canvas* canvas,Pause* pause);
};
