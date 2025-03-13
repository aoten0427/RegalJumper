// ================================================================ 
// �t�@�C���� : ThreadShot.h
// �쐬�� : �i�R�ɓV
// ���� :  �����ˏ��
// ================================================================

#pragma once
#include"Game/Play/Thread/ThreadState/ThreadState.h"
#include"Game/Parameter/ThreadParameter.h"


class ThreadShot :public ThreadState
{
private:
	//��
	Thread* m_thread;
	//��������
	float m_continuationTimer;
	//���̕�
	float m_distance;
	//�p�����[�^
	const ThreadParameter::Parameter* m_parameter;
public:
	//�R���X�g���N�^
	ThreadShot(ThreadStateMachine* machine, Thread* thread);
	//�f�X�g���N�^
	~ThreadShot()override = default;
	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
private:
	//�ĉ���
	void ReAcceleration();
};