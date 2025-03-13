// ================================================================ 
// �t�@�C���� : Thread.h
// �쐬�� : �i�R�ɓV
// ���� :  ��
// ================================================================
#include"pch.h"
#include"Thread.h"
#include"Base/Base.h"
#include"Game/Play/Thread/ThreadState/ThreadStateMachine.h"
#include"Game/Play/Thread/ThreadParticle.h"
#include"Game/Play/Thread/RopeSolver.h"
#include"Game/Play/Thread/ThreadModel.h"
#include"Game/Play/Thread/ThreadHolder.h"
#include"Game/Play/Enemy/Target.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene"></param>
Thread::Thread(Scene* scene):Object(scene)
	, m_ropeSolver{},
	m_threadparticles{},
	m_data{},
	m_ropeDistance{ 5.0f }
{
	//�X�e�[�g�}�V���쐬
	m_machine = std::make_unique<ThreadStateMachine>(this);
	//���[�v�\���o�[�쐬
	m_ropeSolver = AddComponent<RopeSolver>(this);
	//���f���쐬
	scene->AddObject<ThreadModel>(scene, this);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime"></param>
void Thread::ObjectUpdate(float deltatime)
{
	m_machine->Update(deltatime);
}

/// <summary>
/// ����
/// </summary>
/// <param name="holder">�ێ���</param>
/// <param name="position">���ˈʒu</param>
/// <param name="direction">���˕���</param>
/// <param name="target">�^�[�Q�b�g</param>
void Thread::Shot(Object* holder, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 direction, Target* target)
{
	//�f�[�^���Z�b�g
	m_data.m_holder = holder;
	m_data.m_threadHolder = holder->GetComponent<ThreadHolder>();
	m_data.m_startPosition = position;
	m_data.m_direction = direction;
	m_data.m_target = target;
	if (!m_data.m_threadHolder)return;

	//���[�v���A�N�e�B�u��
	m_ropeSolver->SetActive(true);

	//�^�[�Q�b�g���w�肳��Ă���ꍇ�͂�����ɔ��˂���
	if (target)
	{
		m_data.m_direction = target->GetTransform()->GetWorldPosition() - position;
		m_data.m_direction.Normalize();
	}

	m_machine->ChangeState(ThreadState::State::Shot);
}

/// <summary>
/// �f�[�^�N���A
/// </summary>
void Thread::Clear()
{
	for (auto& particle : m_threadparticles)
	{
		particle->Destroy();
	}
	m_threadparticles.clear();
	m_ropeSolver->SetActive(false);
	m_ropeSolver->Clear();
}
