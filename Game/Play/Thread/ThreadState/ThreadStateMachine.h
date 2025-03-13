// ================================================================ 
// �t�@�C���� : ThreadStateMachine.h
// �쐬�� : �i�R�ɓV
// ���� :  ���̏�Ԃ��Ǘ�
// ================================================================
#pragma once
#include"Base/MyLibraries/StateMachine/StateMachine.h"
#include"Game/Play/Thread/ThreadState/ThreadState.h"

class Thread;

class ThreadStateMachine:public StateMachine<ThreadState,ThreadState::State>
{
private:
public:
	//�R���X�g���N�^
	ThreadStateMachine(Thread* thread);
};