// ================================================================ 
// �t�@�C���� : ThreadShot.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �����ˏ��
// ================================================================
#include"pch.h"
#include"ThreadShot.h"
#include"Base/Base.h"
#include"Game/Play/Thread/Thread.h"
#include"Game/Play/Thread/ThreadParticle.h"
#include"Game/Play/Thread/RopeSolver.h"
#include"Game/Play/Thread/Constraint.h"
#include"Game/Play/Thread/Particle.h"
#include"Game/Play/Enemy/Target.h"

//�����p�[�e�B�N����
constexpr int PARTICLE_NUM = 30;
//��������
constexpr float INITIAL_DISTANCE = 0.2f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">���X�e�[�g�}�V��</param>
/// <param name="thread">��</param>
ThreadShot::ThreadShot(ThreadStateMachine* machine, Thread* thread):ThreadState(machine,thread)
	,
	m_thread{thread},
	m_continuationTimer{},
	m_distance{INITIAL_DISTANCE},
	m_parameter{ThreadParameter::PARAMETER()}
{
	
}

/// <summary>
/// ���O�X�V
/// </summary>
void ThreadShot::PreUpdate()
{
	//��{�f�[�^�̃��Z�b�g
	m_continuationTimer = 0;
	m_distance = INITIAL_DISTANCE;

	Scene* scene = m_thread->GetScene();
	//�p�[�e�B�N���̎擾
	std::vector<ThreadParticle*> threadParticle = m_thread->GetThreadParticles();
	//�f�[�^�擾
	Thread::ThreadData data = m_thread->GetData();
	//�p�[�e�B�N���𐶐�
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		//���蔲���t���O(�Ō���݂̂��蔲����h��)
		bool isdetection = i == PARTICLE_NUM - 1;
		UNREFERENCED_PARAMETER(isdetection);
		//�R���C�_�[�����t���O
		bool iscollider = i % 10 == 0 || isdetection;/*true;*/
		//���p�[�c����
		ThreadParticle* addparticle = scene->AddObject<ThreadParticle>(scene, m_thread,iscollider, isdetection);
		threadParticle.emplace_back(addparticle);
		//����ɉғ����邽�߂ɂ킸���ɂ��炷
		addparticle->GetTransform()->Translate(data.m_startPosition);
		addparticle->GetTransform()->Translate(data.m_direction * (i + 1.0f) * 0.01f);
		//�͂�^����
		addparticle->GetRigidbody()->AddForce(data.m_direction * m_parameter->INITIAL_POWER);
	}

	//��[�t���O���I��
	threadParticle.back()->SetIsTip(true);
	//�����d������
	auto rigidbody = threadParticle.back()->GetComponent<Rigidbody>();
	rigidbody->SetMass(3.0f);

	//�����Ȃ���
	RopeSolver* ropeSolver = m_thread->GetRopeSolver();
	//�z���_�[�Ǝ��͂���
	ropeSolver->Conect(data.m_holder, threadParticle.front());
	//�����m
	for (int i = 0; i < threadParticle.size() - 1; i++)
	{
		ropeSolver->Conect(threadParticle[i], threadParticle[i + 1]);
	}

	//�z���_-�ւ̎��̉e�����Ȃ��ɂ���
	Particle* holderParticle = data.m_holder->GetComponent<Particle>();
	holderParticle->SetIsMove(false);
	//���̐�[�ɗ͂�^����
	threadParticle.back()->GetRigidbody()->AddForce(data.m_direction * m_parameter->INITIAL_POWER_TIP);
	//���̒�����ݒ�
	m_thread->SetRopeDistance(m_distance);

	m_thread->SetThreadParticle(threadParticle);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
void ThreadShot::Update(float deltaTime)
{
	//���ԉ��Z
	m_continuationTimer += deltaTime;
	//��̂ق��ɗ͂�^���ĐL�΂�
	ReAcceleration();
	//���񋗗���L�΂�
	m_distance += deltaTime * m_parameter->EXTEND_SPEED;
	m_thread->GetRopeSolver()->SetDistance(m_distance);
	//1�b�o�߂ŏ���
	if (m_continuationTimer > m_parameter->DELETE_TIME)
	{
		ChangeState(ThreadState::State::Cut);
	}
}

/// <summary>
/// ����X�V
/// </summary>
void ThreadShot::PostUpdate()
{
}

/// <summary>
/// �ĉ���
/// </summary>
void ThreadShot::ReAcceleration()
{
	//�p�[�e�B�N���̎擾
	std::vector<ThreadParticle*> threadParticle = m_thread->GetThreadParticles();
	//�f�[�^�擾
	Thread::ThreadData data = m_thread->GetData();
	//��Ȃ�Ԃ�
	if (threadParticle.empty())return;
	if (data.m_target != nullptr)
	{
		//�^�[�Q�b�g�Ɍ������ė͂�^����
		data.m_direction = data.m_target->GetTransform()->GetWorldPosition() - threadParticle.back()->GetTransform()->GetPosition();
		data.m_direction.Normalize();
	}
	else
	{
		DirectX::SimpleMath::Vector3 velocity = threadParticle.back()->GetRigidbody()->GetVelocity();
		velocity.Normalize();
		data.m_direction -= velocity * 0.5f;
		data.m_direction.Normalize();
	}
	//���̐�[�ɗ͂�^����
	threadParticle.back()->GetRigidbody()->AddForce(data.m_direction * m_parameter->ADD_POWER);
}
