// ================================================================ 
// �t�@�C���� : 
// �쐬�� : �i�R�ɓV
// ���� :  
// ================================================================

#pragma once
#include"Game/Play/Thread/ThreadState/ThreadState.h"


class ThreadNone :public ThreadState
{
private:
public:
	ThreadNone(ThreadStateMachine* machine, Thread* thread);
	~ThreadNone()override = default;

	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
};