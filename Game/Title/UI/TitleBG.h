// ================================================================ 
// �t�@�C���� : TitleBG.h
// �쐬�� : �i�R�ɓV
// ���� :  �^�C�g���̔w�i�A���S
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class TitleBG :public UserInterface
{
private:
	//���S
	UserInterface* m_logo;
	//�^�C�}�[
	float m_timer;
public:
	//�R���X�g���N�^
	TitleBG(Canvas* canvas);
	//�f�X�g���N�^
	~TitleBG() override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
};