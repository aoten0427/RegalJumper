// ================================================================ 
// �t�@�C���� : QuitPage.h
// �쐬�� : �i�R�ɓV
// ���� :  �ޏo�y�[�W
// ================================================================
#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"
#include"Base/Canvas/UserInterface/Button.h"

class Pause;

class QButton :public Button
{
public:
	QButton(Canvas* canvas);

	//�}�E�X���m�C�x���g
	void MouseWithinEvent(bool within) override;
};

class QuitPage :public UserInterface
{
private:
public:
	QuitPage(Canvas* canvas,Pause* pause);
};
