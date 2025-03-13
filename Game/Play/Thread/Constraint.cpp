// ================================================================ 
// �t�@�C���� : Constraint.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �p�[�e�B�N�����m�̐�����Ǘ�
// ================================================================
#include"pch.h"
#include"Constraint.h"
#include"Game/Play/Thread/Particle.h"
#include"Base/MyLibraries/Functions.h"
#include"Base/Tween/Easing.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="particle1">�p�[�e�B�N��1</param>
/// <param name="particle2">�p�[�e�B�N��2</param>
Constraint::Constraint(Particle* particle1, Particle* particle2)
	:
	m_lagrange{ 0 },
	m_flexibility{ 0 },
	m_particle1{ particle1 },
	m_particle2{ particle2 },
	m_distance{ 1.5f },
	m_time{0}
{
	//�p�[�e�B�N���Ɏ��M��o�^
	particle1->AddConstraint(this);
	particle2->AddConstraint(this);
}

/// <summary>
/// �p�����[�^�̃��Z�b�g
/// </summary>
/// <param name="lagurange"></param>
/// <param name="flexibillity"></param>
void Constraint::ResetParameter(float lagurange, float flexibillity)
{
	m_lagrange = lagurange;
	m_flexibility = flexibillity;
}

/// <summary>
/// ����ɂ��v�Z�����s
/// </summary>
/// <param name="origin"></param>
/// <param name="deltatime"></param>
void Constraint::Compute(Particle* origin, float deltatime)
{
	m_time += deltatime;

	float lagrange = ComputeLagrange(deltatime);
	DirectX::SimpleMath::Vector3 distance = ComputePosition(lagrange);

	m_lagrange += lagrange;

	//�p�[�e�B�N���̗\���ʒu���X�V
	m_particle1->SetPredictedPosition(m_particle1->GetPredictedPosition() + m_particle1->GetReverseMass() * distance);
	m_particle2->SetPredictedPosition(m_particle2->GetPredictedPosition() - m_particle2->GetReverseMass() * distance);

	//���̃p�[�e�B�N���̌v�Z�����s
	Particle* next = m_particle1 == origin ? m_particle2 : m_particle1;
	next->Step(deltatime, this);
}

/// <summary>
/// ���񋗗���ݒ�
/// </summary>
void Constraint::SetDistance()
{
	using namespace DirectX::SimpleMath;
	//���݂̋����𐧖񋗗��Ƃ���
	Vector3 vector = m_particle2->GetPredictedPosition() - m_particle1->GetPredictedPosition();
	float distance = vector.Length();
	m_distance = distance;
}

/// <summary>
/// �Ȃ����Ă��邩���f
/// </summary>
/// <param name="particle1"></param>
/// <param name="particle2"></param>
/// <returns></returns>
bool Constraint::IsConnect(Particle* particle1, Particle* particle2)
{
	if (particle1 == particle2)return false;
	if (m_particle1 != particle1 && m_particle2 != particle2)return false;
	if (m_particle2 != particle1 && m_particle2 != particle2)return false;

	return true;
}


float Constraint::ComputeLagrange(float deltatime)
{
	using namespace DirectX::SimpleMath;

	// �\���ʒu�̍����x�N�g�����v�Z
	Vector3 vector = m_particle2->GetPredictedPosition() - m_particle1->GetPredictedPosition();
	// ���݂̋������v�Z
	float distance = vector.Length();
	// ������� C = ���݂̋��� - �ݒ肳�ꂽ���񋗗�
	float C = distance - m_distance;
	// �S���̏_����l�������␳�W�����v�Z
	float ��Tilda = m_flexibility / (deltatime * deltatime);
	// �����x�N�g���𐳋K�� (����̌��z)
	Vector3 ��C = vector / distance;
	// �t���ʂ̍��v���擾
	float invM = m_particle1->GetReverseMass() + m_particle2->GetReverseMass();
	// �C�����ꂽ���O�����W���搔���v�Z
	return (C - ��Tilda * m_lagrange) / (��C.Dot(invM * ��C) + ��Tilda);
}

DirectX::SimpleMath::Vector3 Constraint::ComputePosition(float lagrange)
{
	// �\���ʒu�̍����x�N�g�����擾
	auto ��C = (m_particle2->GetPredictedPosition() - m_particle1->GetPredictedPosition());
	// ���K�����ĕ����x�N�g�������߂�
	��C.Normalize();

	// ���O�����W���搔�Ɋ�Â��ʒu�C���ʂ��v�Z
	return ��C * lagrange;
}
