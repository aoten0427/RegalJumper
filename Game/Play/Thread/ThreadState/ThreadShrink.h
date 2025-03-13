// ================================================================ 
// �t�@�C���� : ThreadShrink.h
// �쐬�� : �i�R�ɓV
// ���� :  �����k�ޏ��
// ================================================================

#pragma once
#include"Game/Play/Thread/ThreadState/ThreadState.h"
#include"Game/Parameter/ThreadParameter.h"

class DirectXInputs;

class ThreadShrink :public ThreadState
{
private:
	//��
	Thread* m_thread;
	//���̕�
	float m_initialDistance;
	//�������炷��
	float m_shrinkValue;
	//�ω�����
	float m_ratio;
	//�p�����[�^
	const ThreadParameter::Parameter* m_parameter;
	//�ω���
	float m_changeValue;
	//�ω��C�[�W���O
	std::string m_easingtype;
	//���͋@�\
	DirectXInputs* m_input;

	
public:
	//�R���X�g���N�^
	ThreadShrink(ThreadStateMachine* machine, Thread* thread);
	//�f�X�g���N�^
	~ThreadShrink()override = default;
	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
};