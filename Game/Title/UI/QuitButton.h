#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class Sound;

class QuitButton :public Button
{
private:
	Sound* m_sound;
public:
	QuitButton(Canvas* canvas);
	~QuitButton()override = default;

	//マウス感知イベント
	void MouseWithinEvent(bool within) override;
	//左マウスクリックイベント
	void LeftClickEvent(bool within) override;
};
