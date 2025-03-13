// ================================================================ 
// �t�@�C���� : ResultScore.h
// �쐬�� : �i�R�ɓV
// ���� :  ���U���g�̃X�R�A�\��
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Tween;

class ResultScore :public UserInterface
{
private:
	//�X�R�A�g
	UserInterface* m_mark;
	DirectX::SimpleMath::Vector2 m_markSize;
	Tween* m_markTween;
	//�X�R�A
	UserInterface* m_score;
	DirectX::SimpleMath::Vector2 m_scoreSize;
	Tween* m_scoreTween;
	//�\���J�E���g�^�C�}�[
	float m_timer;
public:
	//�R���X�g���N�^
	ResultScore(Canvas* canvas);
	//�f�X�g���N�^
	~ResultScore() override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
private:
	//�f�[�^�ǂݍ���
	void LoadJSON();
	//�f�[�^��������
	void WriteJSON();
	//Tween�X�L�b�v����
	void Skip();
};