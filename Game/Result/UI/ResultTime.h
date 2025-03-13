// ================================================================ 
// �t�@�C���� : ResultTime.h
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�ł̃^�C���\��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Time;
class Tween;

class ResultTime :public UserInterface
{
private:
	//�N���A����
	Time* m_time;
	DirectX::SimpleMath::Vector2 m_timesize;
	Tween* m_timeTween;
	//�o�[
	UserInterface* m_bar;
	DirectX::SimpleMath::Vector2 m_barsize;
	Tween* m_barTween;
public:
	//�R���X�g���N�^
	ResultTime(Canvas* canvas);
	//�f�X�g���N�^
	~ResultTime()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
private:
	//�X�L�b�v����
	void Skip();
};