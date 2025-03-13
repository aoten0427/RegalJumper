// ================================================================ 
// �t�@�C���� : PauseButton.h
// �쐬�� : �i�R�ɓV
// ���� :  �|�[�Y�ň����{�^��
// ================================================================
#pragma once
#include"Base/Canvas/UserInterface/Button.h"

class PauseButton :public Button
{
public:
	//�I���^�C�v
	enum class TYPE
	{
		RESTART,
		STAGESELECT,
		OPTION,
		QUIT
	};
private:
public:
	//�R���X�g���N�^
	PauseButton(Canvas* canvas,TYPE type);
	//�f�X�g���N�^
	~PauseButton()override = default;

	//�}�E�X���m�C�x���g
	void MouseWithinEvent(bool within) override;
	//���N���b�N�C�x���g
	void LeftClickEvent(bool within) override;
private:
	//�f�[�^�Z�b�g
	void SetData(TYPE type);
};