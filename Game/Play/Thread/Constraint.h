// ================================================================ 
// �t�@�C���� : Constraint.h
// �쐬�� : �i�R�ɓV
// ���� :  �p�[�e�B�N�����m�̐�����Ǘ�
// ================================================================

#pragma once
#include <SimpleMath.h>

class Particle;

class Constraint
{
private:
	//���O�����W���搔
	float m_lagrange;
	//�_�
	float m_flexibility;

	//�q����p�[�e�B�N��
	Particle* m_particle1;
	Particle* m_particle2;
	//���񋗗�
	float m_distance;
	//
	float m_time;
public:
	//�R���X�g���N�^
	Constraint(Particle* particle1, Particle* particle2);
	//�f�X�g���N�^
	~Constraint() = default;
	//�p�����[�^�̃��Z�b�g
	void ResetParameter(float lagurange, float flexibillity);
	//����ɂ��v�Z�����s
	void Compute(Particle* origin, float deltatime);
	//���񋗗���ݒ�
	void SetDistance(float distance) { m_distance = distance; }
	//���݂̋������琧�񋗗���ݒ�
	void SetDistance();
	//�Ȃ����Ă��邩���f
	bool IsConnect(Particle* particle1, Particle* particle2);
private:
	float ComputeLagrange(float deltatime);
	DirectX::SimpleMath::Vector3 ComputePosition(float lagrange);
};