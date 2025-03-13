// ================================================================ 
// �t�@�C���� : PauseExitButton.h
// �쐬�� : �i�R�ɓV
// ���� :  �|�[�Y�ޏo�{�^��
// ================================================================

#pragma once
#include"Base/Canvas//UserInterface/Button.h"

class PauseExitButton :public Button
{
private:
public:
	//�R���X�g���N�^
	PauseExitButton(Canvas* canvas);
	//�f�X�g���N�^
	~PauseExitButton()override = default;

	//�}�E�X���m�C�x���g
	void MouseWithinEvent(bool within) override;
	//���N���b�N�C�x���g
	void LeftClickEvent(bool within) override;
};