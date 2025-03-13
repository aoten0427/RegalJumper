// ================================================================ 
// �t�@�C���� : Target.h
// �쐬�� : �i�R�ɓV
// ���� :  �^�[�Q�b�g
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class Sphere;
class Search;
template<typename...Args>
class Subject;
template<typename...Args>
class Observer;

class Target :public Object
{
private:
	//����ID
	static int TARGET_ID;
public:
	//�^�[�Q�b�g�̃^�C�v
	enum class TargetType
	{
		Move,
		Attack,
		Player
	};
public:
	//�^�O�擾
	ObjectTag GetTag() { return ObjectTag::Target; };
	//�^�C�v�擾
	TargetType GetType()const { return m_type; }
	//�A�N�e�B�u�ݒ�
	void SetTargetActive(bool active) { m_isActive = active; }
	bool GetTargetActive()const { return m_isActive; }
	//�^�[�Q�b�g�ݒ�
	void SetIsTarget(const bool& Target) { m_isTarget = Target; }
	bool GetIsTarget()const { return m_isTarget; }
private:
	//���g��ID
	int m_id;
	//�^�[�Q�b�g�^�C�v
	TargetType m_type;
	//�z���_�[
	Object* m_holder;
	//����
	Sphere* m_collider;
	//�A�N�e�B�u(�͈͓��ɓ����Ă��邩)
	bool m_isActive;
	//�^�[�Q�b�g(�^�[�Q�b�g�ɂȂ��Ă��邩)
	bool m_isTarget;
	//�j�󎞂ɌĂяo���T�u�W�F�N�g
	Subject<>* m_destroySubject;
public:
	//�R���X�g���N�g
	Target(Scene* scene, Object* holder, TargetType type);
	//�f�X�g���N�^
	~Target()override;
	//�͈͂ɓ����Ă��邩
	bool IsRange(const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& dire,
		const float& range,
		const float& vision);
	//�T�[�`���[�̓o�^�A����
	void SetSearch(Observer<>* observer);
	void RemoveSearch(Observer<>* observer);
	//Trigger�̎��s�L��
	bool IsTriggerAct(Collider* collider) override;
};
