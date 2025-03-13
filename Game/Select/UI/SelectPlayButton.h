// ================================================================ 
// �t�@�C���� : SelectPlayButton.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�V�[���ڍs�{�^��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

template<typename...Args>
class Subject;

class SelectPlayButton :public Button
{
private:
	//�F�ύXUI
	UserInterface* m_bg;
	//�N���b�N���ʒm
	Subject<>* m_ClickSubject;
public:
	//�R���X�g���N�^
	SelectPlayButton(Canvas* canvas);
	//�f�X�g���N�^
	~SelectPlayButton()override = default;
	//�}�E�X���m�C�x���g
	void MouseWithinEvent(bool within);
	//���N���b�N�C�x���g
	void LeftClickEvent(bool within);
};