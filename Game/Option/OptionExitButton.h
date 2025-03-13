// ================================================================ 
// �t�@�C���� : OptionExitButton.h
// �쐬�� : �i�R�ɓV
// ���� :  �I�v�V�����ޏo�{�^��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class Option;

class OptionExit :public Button
{
private:
public:
	//�R���X�g���N�^
	OptionExit(Canvas* canvas,Option* option);
	//�f�X�g���N�^
	~OptionExit() override = default;
	//�}�E�X���m�C�x���g
	void MouseWithinEvent(bool within)override;
};
