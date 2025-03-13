// ================================================================ 
// �t�@�C���� :Player.h 
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[
// ================================================================

#pragma once
#include"Base/Object/Object.h"


class Rigidbody;
class OBB;
class PlayerStateMachine;
class PlayerCenter;
class SpiderModels;
class PlayCamera;
template<typename...Args>
class Subject;
template<typename...Args>
class Observer;

class Player :public Object
{
public:
	//�^�O�擾
	ObjectTag GetTag() { return ObjectTag::Player; };
	//�v���C���[�Z���^�[�擾
	PlayerCenter* GetPlayerCenter() const { return m_playerCenter; }
	//���f���擾
	SpiderModels* GetModel() const { return m_model; }
	//�n��L���擾
	bool GetIsGround() const { return m_isGround; }
private:
	PlayerCenter* m_playerCenter;
	OBB* m_collider;
	Rigidbody* m_rigidbody;
	//���f��
	SpiderModels* m_model;
	//�X�e�[�g�}�V��
	std::unique_ptr<PlayerStateMachine> m_stateMachine;
	//�n�㔻��
	bool m_isGround;
	//�J����
	PlayCamera* m_camera;
	//���S���T�u�W�F�N�g
	Subject<>* m_deathSubject;
	//���Z�b�g�I�u�U�[�o�[
	Observer<>* m_resetObserver;
public:
	//�R���X�g���N�^
	Player(Scene* scene,PlayerCenter* center);
	//�f�X�g���N�^
	~Player()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
	//�o������
	void Entery();

	//����n
	//Trigger�̎��s�L��
	bool IsTriggerAct(Collider* collider) override;
	//Collision�̎��s�L��
	bool IsCollisionAct(Collider* collider) override;
	//�����߂�(�����o����)
	void PushBack(DirectX::SimpleMath::Vector3 pushback)override;
	//Trigger����
	void OnTrigger(Collider* collider) override;
	//Collision����
	void OnCollision(Collider* collider) override;
	//�߂荞�݌v�Z���s�̗L��
	bool IsDetectionAct(Collider* collider)override;

	//�f�[�^���Z�b�g
	void Reset();

private:
	//�S�[������
	void IsGoal();
	//���S����
	void IsDeath();
};