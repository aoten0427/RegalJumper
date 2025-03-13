// ================================================================ 
// �t�@�C���� : ThreadCut.h
// �쐬�� : �i�R�ɓV
// ���� :  �����؂����
// ================================================================

#pragma once
#include"Game/Play/Thread/ThreadState/ThreadState.h"


class ThreadCut :public ThreadState
{
private:
	//��
	Thread* m_thread;
public:
	//�R���X�g���N�^
	ThreadCut(ThreadStateMachine* machine, Thread* thread);
	//�f�X�g���N�^
	~ThreadCut()override = default;
	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
};