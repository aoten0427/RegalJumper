// ================================================================ 
// �t�@�C���� : Particle.h
// �쐬�� : �i�R�ɓV
// ���� :  XPBD�ɗp����p�[�e�B�N��
// ================================================================

#pragma once
#include"Base/Component/Component.h"

class Rigidbody;
class Constraint;

class Particle :public Component
{
public:
	//�\���ʒu��Ԃ�
	DirectX::SimpleMath::Vector3 GetPredictedPosition() { return m_predictedPosition; }
	//�\���ʒu���Z�b�g
	void SetPredictedPosition(const DirectX::SimpleMath::Vector3& position) { m_predictedPosition = position; }
	//�t�d����Ԃ�
	float GetReverseMass() const { return m_reverseMass; }
	//���W�b�h�{�f�B�擾
	Rigidbody* GetRigidbody() { return m_rigidbody; }
	//�ړ��t���O�Z�b�g
	bool GetIsMove() { return m_isMove; }
	//�ړ��t���O�擾
	void SetIsMove(bool move) { m_isMove = move; }
private:
	//���W�b�h�{�f�B	
	Rigidbody* m_rigidbody;
	//�Ȃ���
	std::vector<Constraint*> m_constraint;
	//�\���ʒu
	DirectX::SimpleMath::Vector3 m_predictedPosition;
	//���]�d��
	float m_reverseMass;
	//�X�V�m�F
	bool m_isStep;
	//�O�t���[�����W
	DirectX::SimpleMath::Vector3 m_backPosition;
	//�ړ��t���O
	bool m_isMove;
public:
	Particle(Object* object);
	~Particle() override = default;
	//�A�b�v�f�[�g
	void UpdatePosition(float deltaTime);
	//�v�Z�X�V
	void Step(float deltatime, Constraint* origin = nullptr);
	//�X�V�t���O���Z�b�g
	void ReStart() { m_isStep = false; }
	//�Ȃ���ǉ�
	void AddConstraint(Constraint* constraint);
	//�Ȃ���폜
	void DeleteConstraint(Constraint* constraint);
	//�Ȃ���̌���Ԃ�
	int GetConstraintNum() { return (int)m_constraint.size(); }
	//�f�[�^�̃N���A
	void Clear();
};