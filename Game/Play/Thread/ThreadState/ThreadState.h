// ================================================================ 
// �t�@�C���� : ThreadState.h
// �쐬�� : �i�R�ɓV
// ���� :  ���̏�Ԋ��N���X
// ================================================================

#pragma once
#include"Base/MyLibraries/StateMachine/IState.h"

class Thread;
class ThreadStateMachine;

class ThreadState :public IState
{
public:
	//���
	enum class State
	{
		None,
		Shot,
		Shrink,
		Paste,
		Cut,
		Attack
	};
private:
	//�X�e�[�g�}�V��
	ThreadStateMachine* m_machine;
public:
	//�R���X�g���N�^
	ThreadState(ThreadStateMachine* machine, Thread* thread);
	//�f�X�g���N�^
	virtual ~ThreadState()override = default;
	//��ԕω�
	void ChangeState(State state);
};