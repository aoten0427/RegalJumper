// ================================================================ 
// �t�@�C���� : ThreadState.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ���̏�Ԋ��N���X
// ================================================================
#include"pch.h"
#include"ThreadState.h"
#include"Game/Play/Thread/ThreadState/ThreadStateMachine.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">���X�e�[�g�}�V��</param>
/// <param name="thread">��</param>
ThreadState::ThreadState(ThreadStateMachine* machine, Thread* thread)
	:
	m_machine{machine}
{
	UNREFERENCED_PARAMETER(thread);
}

/// <summary>
/// ��ԕω�
/// </summary>
/// <param name="state">�ύX�X�e�[�g</param>
void ThreadState::ChangeState(State state)
{
	m_machine->ChangeState(state);
}
