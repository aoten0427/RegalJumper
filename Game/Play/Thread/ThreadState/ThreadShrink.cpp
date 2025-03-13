// ================================================================ 
// �t�@�C���� : ThreadShrink.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �����k�ޏ��
// ================================================================
#include"pch.h"
#include"ThreadShrink.h"
#include"Base/Base.h"
#include"Game/Play/Thread/Thread.h"
#include"Game/Play/Thread/ThreadParticle.h"
#include"Game/Play/Thread/RopeSolver.h"
#include"Game/Play/Thread/Constraint.h"
#include"Game/Play/Thread/Particle.h"
#include"Game/Play/Thread/ThreadHolder.h"
#include"Base/Tween/DoTween.h"

constexpr float SHRINK_MIN = 0.01f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">���X�e�[�g�}�V��</param>
/// <param name="thread">��</param>
ThreadShrink::ThreadShrink(ThreadStateMachine* machine, Thread* thread) :ThreadState(machine, thread)
	,
	m_thread{thread},
	m_initialDistance{ 0 },
	m_shrinkValue{ 0 },
	m_ratio{0},
	m_parameter{ThreadParameter::PARAMETER()},
	m_changeValue{0}
{
	m_input = thread->GetCommonResources()->GetInput();
}

/// <summary>
/// ���O�X�V
/// </summary>
void ThreadShrink::PreUpdate()
{
	using namespace DirectX::SimpleMath;

	//�f�[�^�̃��Z�b�g
	m_initialDistance = 0;
	m_shrinkValue = m_parameter->SHRINK_VALUE_BEGIN;
	m_changeValue = m_parameter->SHRINK_VALUE_BEGIN - m_parameter->SHRINK_VALUE_END;
	m_easingtype = m_parameter->SHRINK_EASING;

	//�f�[�^�擾
	Thread::ThreadData data = m_thread->GetData();
	//�p�[�e�B�N���̎擾
	std::vector<ThreadParticle*> threadParticle = m_thread->GetThreadParticles();
	//�z���_-�ւ̎��̉e��������ɂ���
	Particle* holderParticle = data.m_holder->GetComponent<Particle>();
	if (holderParticle == nullptr)return;
	holderParticle->SetIsMove(true);

	//�[���Œ�
	threadParticle.back()->GetRigidbody()->SetFixed(true);
	//�X�s�[�h�����Z�b�g
	for (auto& particle : threadParticle)
	{
		particle->GetRigidbody()->SetAddForce(Vector3::Zero);
		particle->GetRigidbody()->SetMass(1.0f);
	}
	//���񋗗��̒���
	Vector3 begin = threadParticle.front()->GetTransform()->GetWorldPosition();
	Vector3 end = threadParticle.back()->GetTransform()->GetWorldPosition();
	float lenth = Vector3::Distance(begin, end);
	float distance = lenth / (threadParticle.size()) * 0.9f;
	//���[�v�\���o�[�ɏ���ݒ�
	m_thread->GetRopeSolver()->SetFlexibility(0.0001f);
	m_initialDistance = distance;
	m_thread->GetRopeSolver()->SetDistance(m_initialDistance);
	//Conect�ʒm
	data.m_threadHolder->Conect();

	m_thread->SetThreadParticle(threadParticle);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
void ThreadShrink::Update(float deltaTime)
{
	//�ω������𒲐�
	m_ratio += deltaTime * m_parameter->SHRINK_SPEED;
	if (m_ratio > 1)m_ratio = 0;
	//�k�܂���ʂ�ω�
	m_shrinkValue = (1 - Easing::Selection(Easing::GetEase(m_easingtype), m_ratio)) * m_changeValue + m_parameter->SHRINK_VALUE_END;
	//���̕����k�܂���
	m_initialDistance -= deltaTime * m_shrinkValue;
	if (m_initialDistance <= SHRINK_MIN)m_initialDistance = SHRINK_MIN;
	//���̕���ݒ�
	m_thread->GetRopeSolver()->SetDistance(m_initialDistance);

	//���}�E�X�������ꂽ�玅��؂�
	if (m_input->GetMouseTracker()->leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::UP)
	{
		ChangeState(State::Cut);
	}
}

/// <summary>
/// ����X�V
/// </summary>
void ThreadShrink::PostUpdate()
{
}
