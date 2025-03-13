// ================================================================ 
// �t�@�C���� : ThreadCut.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �����؂����
// ================================================================
#include"pch.h"
#include"ThreadCut.h"
#include"Game/Play/Thread/Thread.h"
#include"Game/Play/Thread/ThreadHolder.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">���X�e�[�g�}�V��</param>
/// <param name="thread">��</param>
ThreadCut::ThreadCut(ThreadStateMachine* machine, Thread* thread) :ThreadState(machine, thread)
	,
	m_thread{thread}
{
}

/// <summary>
/// ���O�X�V
/// </summary>
void ThreadCut::PreUpdate()
{
	//�J�b�g�ʒm
	m_thread->GetData().m_threadHolder->Cut();
	//���ɃN���A����
	m_thread->Clear();
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
void ThreadCut::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/// <summary>
/// ����X�V
/// </summary>
void ThreadCut::PostUpdate()
{
}
