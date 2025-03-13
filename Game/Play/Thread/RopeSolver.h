// ================================================================ 
// �t�@�C���� : RopeSolver.h
// �쐬�� : �i�R�ɓV
// ���� :  ��̎��̌v�Z���Ǘ�
// ================================================================

#pragma once
#include"Base/Component/Component.h"

class Constraint;
class Particle;
class Rigidbody;

class RopeSolver :public Component
{
private:
	//�p�[�e�B�N��
	std::vector<Particle*> m_particles;
	//�p�[�e�B�N���Ԃ̐���
	std::vector<std::unique_ptr<Constraint>> m_constraints;

	float m_flexibility;
public:
	//�R���X�g���N�^
	RopeSolver(Object* object);
	//�f�X�g���N�^
	~RopeSolver()override = default;
	//�A�b�v�f�[�g
	void Update(float deltaTime);
	//�q����
	void Conect(Object* object1, Object* object2);
	//���񋗗��ݒ�
	void SetDistance(float distance);
	//���񋗗��ݒ�
	void SetDistance();

	void SetFlexibility(float flexibility) { m_flexibility = flexibility; }
	//�Ȃ���̍폜
	void DeleteConstraint(Constraint* constraint);
	//�p�[�e�B�N���̍폜
	void DeleteParticle(Particle* particle);
	//�p�[�e�B�N���擾
	const std::vector<Particle*> GetParticles() { return m_particles; }
	//�f�[�^�N���A
	void Clear();
};