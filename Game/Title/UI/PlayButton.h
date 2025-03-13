// ================================================================ 
// �t�@�C���� : PlayButton.h
// �쐬�� : �i�R�ɓV
// ���� :  �^�C�g����ʂł̃v���C�{�^��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class Sound;

class PlayButton :public Button
{
private:
	Sound* m_sound;
public:
	//�R���X�g���N�^
	PlayButton(Canvas* canvas);
	//�f�X�g���N�^
	~PlayButton() override = default;
	//�}�E�X���m�C�x���g
	void MouseWithinEvent(bool within) override;
	//���}�E�X�N���b�N�C�x���g
	void LeftClickEvent(bool within) override;
};
