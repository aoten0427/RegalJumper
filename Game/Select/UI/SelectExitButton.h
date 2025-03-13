// ================================================================ 
// �t�@�C���� : SelectExitButton.h
// �쐬�� : �i�R�ɓV
// ���� :  �Z���N�g�V�[���ޏo�{�^��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class SelectExitButton :public Button
{
private:
	UserInterface* m_str;
public:
	//�R���X�g���N�^
	SelectExitButton(Canvas* canvas);
	//�f�X�g���N�^
	~SelectExitButton()override = default;
	//�}�E�X���m�C�x���g
	void MouseWithinEvent(bool within);
	//���N���b�N�C�x���g
	void LeftClickEvent(bool within);
};