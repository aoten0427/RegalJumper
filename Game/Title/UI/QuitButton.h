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

	//�}�E�X���m�C�x���g
	void MouseWithinEvent(bool within) override;
	//���}�E�X�N���b�N�C�x���g
	void LeftClickEvent(bool within) override;
};
