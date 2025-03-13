// ================================================================ 
// �t�@�C���� : Particle.cpp
// �쐬�� : �i�R�ɓV
// ���� :  XPBD�ɗp����p�[�e�B�N��
// ================================================================
#include"pch.h"
#include"Particle.h"
#include"Base/Base.h"
#include"Game/Play/Thread/Constraint.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object"></param>
Particle::Particle(Object* object):Component(object)
	,
	m_rigidbody{ nullptr },
	m_constraint{},
	m_predictedPosition{ DirectX::SimpleMath::Vector3::Zero },
	m_reverseMass{0},
	m_isStep{ false },
	m_backPosition{ DirectX::SimpleMath::Vector3::Zero },
	m_isMove{ true }
{
	//���W�b�h�{�f�B�擾
	m_rigidbody = object->GetComponent<Rigidbody>();
	assert(m_rigidbody != nullptr && "���W�b�h�{�f�B������܂���");
	//�v�Z�ɕK�v�ȃf�[�^�擾
	m_reverseMass = 1 / m_rigidbody->GetMass();
	m_backPosition = m_rigidbody->GetPosition() - m_rigidbody->GetVelocity();
}

/// <summary>
/// �ʒu�X�V
/// </summary>
/// <param name="deltaTime"></param>
void Particle::UpdatePosition(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	DirectX::SimpleMath::Vector3 pos = m_rigidbody->GetPosition();
	//�ړ��ʂ��瑬�x���t�Z
	DirectX::SimpleMath::Vector3 vel = pos - m_backPosition;
	//�\���ʒu���X�V
	m_predictedPosition = pos + vel;
	//�ʒu��ۑ�
	m_backPosition = pos;
}

/// <summary>
/// �v�Z�X�V
/// </summary>
/// <param name="deltatime"></param>
/// <param name="origin"></param>
void Particle::Step(float deltatime, Constraint* origin)
{
	//���̉�Ɏ��s���Ă��Ȃ���Ύ��s
	if (m_isStep)return;
	m_isStep = true;
	for (int i = 0; i < m_constraint.size(); i++)
	{
		if (m_constraint[i] == origin)continue;
		m_constraint[i]->Compute(this, deltatime);
	}
}

/// <summary>
/// �Ȃ���ǉ�
/// </summary>
/// <param name="constraint"></param>
void Particle::AddConstraint(Constraint* constraint)
{
	auto add = std::find(m_constraint.begin(), m_constraint.end(), constraint);
	if (add != m_constraint.end())return;
	m_constraint.push_back(constraint);
}

/// <summary>
/// �Ȃ���폜
/// </summary>
/// <param name="constraint"></param>
void Particle::DeleteConstraint(Constraint* constraint)
{
	auto del = std::find(m_constraint.begin(), m_constraint.end(), constraint);
	if (del == m_constraint.end())return;
	m_constraint.erase(del);
}

/// <summary>
/// �f�[�^�̃N���A
/// </summary>
void Particle::Clear()
{
	m_reverseMass = 1 / m_rigidbody->GetMass();
	m_backPosition = m_rigidbody->GetPosition() - m_rigidbody->GetVelocity();
	m_constraint.clear();
}
