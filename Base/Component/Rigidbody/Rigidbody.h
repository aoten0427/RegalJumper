// ================================================================ 
// �t�@�C���� : Rigidbody.h
// �쐬�� : �i�R�ɓV
// ���� :  �I�u�W�F�N�g�̈ړ����Ǘ�����
// ================================================================

#pragma once
#include"Base/Component/Component.h"

class Rigidbody :public Component
{
public:
	//�̏d�擾
	float GetMass() const { return m_mass; }
	//�̏d�ݒ�
	void SetMass(float mass) { m_mass = mass; }
	//���x�擾
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	//���x�ݒ�
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	//�ǉ����x�擾
	DirectX::SimpleMath::Vector3 GetAddforce() const { return m_addforce; }
	//�ǉ����x�ݒ�
	void SetAddForce(const DirectX::SimpleMath::Vector3& addforce) { m_addforce = addforce; }
	//�ǉ����x����
	void AddForce(const DirectX::SimpleMath::Vector3& addforce) { m_addforce += addforce; }
	//�Œ�t���O�擾
	bool GetFixed() const { return m_isFixed; }
	//�Œ�t���O�ݒ�
	void SetFixed(float fixed) { m_isFixed = fixed; }
	//�y�����Z�b�g
	void SetReduction(float reduction) { m_reduction = reduction; }
	//���蔲���t���O�擾
	bool GetIsDetection() const { return m_isDetection; }
private:
	//�̏d
	float m_mass;
	//���x
	DirectX::SimpleMath::Vector3 m_velocity;
	//�ǉ����x
	DirectX::SimpleMath::Vector3 m_addforce;
	//�Œ�t���O
	bool m_isFixed;
	//�X�s�[�h�y����
	float m_reduction;
	//���蔲���h�~
	bool m_isDetection;
public:
	//�R���X�g���N�^
	Rigidbody(Object* object);
	//�f�X�g���N�^
	~Rigidbody();
	//�X�s�[�h�̌v�Z
	void Compute(float deltatime);
	//�|�W�V������Ԃ�
	DirectX::SimpleMath::Vector3 GetPosition();
};