// ================================================================ 
// �t�@�C���� : OptionButton.h
// �쐬�� : �i�R�ɓV
// ���� :  �^�C�g����ʂł̃I�v�V�����{�^��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class Sound;

class OptionButton :public Button
{
private:
	Sound* m_sound;
public:
	//�R���X�g���N�^
	OptionButton(Canvas* canvas);
	//�f�X�g���N�^
	~OptionButton() override = default;
	//�}�E�X���m�C�x���g
	void MouseWithinEvent(bool within);
	//���}�E�X�N���b�N�C�x���g
	void LeftClickEvent(bool within);
};