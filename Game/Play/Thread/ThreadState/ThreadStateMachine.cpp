// ================================================================ 
// �t�@�C���� : ThreadStateMachine.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ���̏�Ԃ��Ǘ�
// ================================================================
#include"pch.h"
#include"ThreadStateMachine.h"
#include"Game/Play/Thread/ThreadState/ThreadNone.h"
#include"Game/Play/Thread/ThreadState/ThreadShot.h"
#include"Game/Play/Thread/ThreadState/ThreadCut.h"
#include"Game/Play/Thread/ThreadState/ThreadShrink.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="thread">��</param>
ThreadStateMachine::ThreadStateMachine(Thread* thread)
{
	AddState(std::make_unique<ThreadNone>(this, thread), ThreadState::State::None);
	AddState(std::make_unique<ThreadShot>(this, thread), ThreadState::State::Shot);
	AddState(std::make_unique<ThreadCut>(this, thread), ThreadState::State::Cut);
	AddState(std::make_unique<ThreadShrink>(this, thread), ThreadState::State::Shrink);

	SetStart(ThreadState::State::None);
}
