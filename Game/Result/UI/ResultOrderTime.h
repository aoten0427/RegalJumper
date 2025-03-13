// ================================================================ 
// �t�@�C���� : ResultOrderTime.h
// �쐬�� : �i�R�ɓV
// ���� :  �ڕW���Ԃ̕\��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Time;
class Tween;

class ResultOrderTIme :public UserInterface
{
private:
	//�e�X�R�A�\��UI
	UserInterface* m_score[3];
	Time* m_orderTimes[3];
	//�A���t�@�l�ω��pTween
	Tween* m_tween;
	//�A���t�@�l
	float m_alpha;
	//
	UserInterface* m_mouse;
public:
	//�R���X�g���N�^
	ResultOrderTIme(Canvas* canvas);
	//�f�X�g���N�^
	~ResultOrderTIme()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
private:
	//�f�[�^�ǂݍ���
	void LoadData();
	//Tween�X�L�b�v����
	void Skip();
};