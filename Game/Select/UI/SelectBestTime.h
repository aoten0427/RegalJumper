// ================================================================ 
// �t�@�C���� : SelectBestTime.h
// �쐬�� : �i�R�ɓV
// ���� :  �X�e�[�W�Z���N�g�ł̃x�X�g�^�C��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Time;
template<typename...Args>
class Observer;

class SelectBestTime :public UserInterface
{
private:
	//�ō��L�^
	Time* m_bestTime;
	//�ڕW����
	Time* m_orderTimes[3];
	//�ō��L�^�̃X�R�A�}�[�N
	UserInterface* m_scoreMarks[2];
	//�X�e�[�W�ύX�I�u�U�[�o�[
	Observer<>* m_observer;
public:
	//�R���X�g���N�^
	SelectBestTime(Canvas* canvas);
	//�f�X�g���N�^
	~SelectBestTime()override = default;
	//�f�[�^�X�V
	void DataUpdate();
private:
	//�f�[�^�ǂݍ���
	void LoadData();
};