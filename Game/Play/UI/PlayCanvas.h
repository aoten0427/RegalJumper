// ================================================================ 
// �t�@�C���� : PlayCanvas.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C�V�[���L�����o�X
// ================================================================

#pragma once
#include"Game/GameCanvas.h"

template<typename...Args>
class Observer;
class Time;

class PlayCanvas :public GameCanvas
{
private:
	//���U���g�J�ڎ��I�u�U�[�o�[
	Observer<>* m_finishObserver;
	//�o�ߎ���
	float m_gameTimer;
	//�^�C�}�[
	class Time* m_time;
public:
	//�R���X�g���N�^
	PlayCanvas(Scene* scene);
	//�f�X�g���N�^
	~PlayCanvas()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
};