// ================================================================ 
// �t�@�C���� : RopeSolver.cpp
// �쐬�� : �i�R�ɓV
// ���� :  ��̎��̌v�Z���Ǘ�
// ================================================================
#include"pch.h"
#include"RopeSolver.h"
#include"Base/Base.h"
#include"Game/Play/Thread/Particle.h"
#include"Game/Play/Thread/Constraint.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object"></param>
RopeSolver::RopeSolver(Object* object):Component(object)
	,
	m_particles{},
	m_constraints{},
	m_flexibility{ 0.000001f }
{
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime"></param>
void RopeSolver::Update(float deltaTime)
{
	if (!GetActive())return;
	if (m_particles.size() == 0)return;
	if (GetObject()->GetScene()->GetState() != Scene::State::PLAY)return;

	//�\�����W���v�Z
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i]->UpdatePosition(deltaTime);
	}

	//�p�����[�^�[��ݒ�
	for (auto&& constraint : m_constraints)
	{
		constraint->ResetParameter(0, 0.0000001f);
	}

	//���W���v�Z
	for (int i = 0; i < 20; i++)
	{
		m_particles[0]->Step(deltaTime);

		for (int j = 0; j < m_particles.size(); j++)
		{
			m_particles[j]->ReStart();
		}
	}

	//�e�p�[�e�B�N���ɗ\���ʒu���瑬�x�����Z
	for (auto& particle : m_particles)
	{
		Rigidbody* rididbody = particle->GetRigidbody();

		//�Œ�I�u�W�F�N�g�����O
		if (rididbody->GetFixed())continue;
		if (!particle->GetIsMove())continue;

		using namespace DirectX::SimpleMath;

		Vector3 pos = rididbody->GetPosition();
		//�\���ʒu�ƌ��݂̈ʒu���瑬�x���t�Z
		Vector3 vel = (particle->GetPredictedPosition() - pos) / deltaTime;
		vel -= rididbody->GetVelocity() / deltaTime;
		//���x�����Z
		rididbody->AddForce(vel);

	}
}

/// <summary>
/// �q����
/// </summary>
/// <param name="object1"></param>
/// <param name="object2"></param>
void RopeSolver::Conect(Object* object1, Object* object2)
{
	//�p�[�e�B�N�����Ȃ��ꍇ�͂���
	Particle* particle1 = object1->GetComponent<Particle>();
	Particle* particle2 = object2->GetComponent<Particle>();
	//�Ȃ��ꍇ����
	if (particle1 == nullptr)particle1 = object1->AddComponent<Particle>(object1);
	if (particle2 == nullptr)particle2 = object2->AddComponent<Particle>(object2);
	//������
	particle1->Clear();
	particle2->Clear();


	if (std::find(m_particles.begin(), m_particles.end(), particle1) == m_particles.end())m_particles.push_back(particle1);
	if (std::find(m_particles.begin(), m_particles.end(), particle2) == m_particles.end())m_particles.push_back(particle2);

	m_constraints.emplace_back(new Constraint(particle1, particle2));
}

/// <summary>
/// ���񋗗���ݒ�
/// </summary>
/// <param name="distance"></param>
void RopeSolver::SetDistance(float distance)
{
	for (auto& constraint : m_constraints)
	{
		constraint->SetDistance(distance);
	}
}

/// <summary>
/// ���݂̋������琧�񋗗���ݒ�
/// </summary>
void RopeSolver::SetDistance()
{
	for (auto& constraint : m_constraints)
	{
		constraint->SetDistance();
	}
}

/// <summary>
/// �Ȃ�����폜
/// </summary>
/// <param name="constraint"></param>
void RopeSolver::DeleteConstraint(Constraint* constraint)
{
	auto constriantItre = std::find_if(m_constraints.begin(), m_constraints.end(), [constraint]
	(const std::unique_ptr<Constraint>& x) {return x.get() == constraint; });
	if (constriantItre == m_constraints.end())return;
	m_constraints.erase(constriantItre);
}

/// <summary>
/// �p�[�e�B�N�����폜
/// </summary>
/// <param name="particle"></param>
void RopeSolver::DeleteParticle(Particle* particle)
{
	auto particleItre = std::find(m_particles.begin(), m_particles.end(), particle);
	if (particleItre == m_particles.end())return;
	m_particles.erase(particleItre);
}

/// <summary>
/// �f�[�^�̃N���A
/// </summary>
void RopeSolver::Clear()
{
	for (auto& particle : m_particles)
	{
		particle->Destroy();
	}
	m_particles.clear();
	m_constraints.clear();
}


