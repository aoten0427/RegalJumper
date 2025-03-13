// ================================================================ 
// �t�@�C���� : ThreadParticle.h
// �쐬�� : �i�R�ɓV
// ���� :  ���̍ŏ��P��
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class Thread;
class Rigidbody;

class ThreadParticle :public Object
{
public:
	//��[�ݒ�
	void SetIsTip(bool tip) { m_isTip = tip; }
	//���W�b�h�{�f�B�擾
	Rigidbody* GetRigidbody() { return m_rigidbody; }
private:
	//���S��
	Thread* m_thread;
	//���W�b�h�{�f�B
	Rigidbody* m_rigidbody;
	//��[����
	bool m_isTip;
public:
	//�R���X�g���N�^
	ThreadParticle(Scene* scene, Thread* thread, bool iscollider, bool isdetection);
	//�f�X�g���N�^
	~ThreadParticle()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
	//Collision���s�L��
	bool IsCollisionAct(Collider* collider) override;
	//Collision����
	void OnCollision(Collider* collider)override;

	bool IsDetectionAct(Collider* collider) override;
};


