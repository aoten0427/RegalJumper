// ================================================================ 
// �t�@�C���� : CollisionManager.h
// �쐬�� : �i�R�ɓV
// ���� :  �Փ˔�����Ǘ�
// ================================================================

#pragma once
#include"Base/Component/Collider/Collider.h"

class Rigidbody;

class CollisionManager
{
private:
	//�Փ˔���I�u�W�F�N�g���
	struct  CollisionData
	{
		Object* m_holder;     //�ێ���
		Collider* m_collider;   //�Փ˔���
		Rigidbody* m_rigidbody;  //�ێ����W�b�h�{�f�B
		CollisionType m_type;       //����^�C�v
	};
private:
	////�Ǘ��Փ˃f�[�^
	std::vector<CollisionData> m_collisionDates;
	//���蔲����h�~���郊�W�b�h�{�f�B
	/*std::unordered_set<Rigidbody*> m_detectionObject;*/
public:
	//�R���X�g���N�^
	CollisionManager();
	//�f�X�g���N�^
	~CollisionManager() = default;
	//�A�b�v�f�[�g
	void Update();

	//�R���C�_�[�ǉ�
	void AddCollider(Collider* collider, CollisionType type);
	//�R���C�_�[�폜
	void ReMoveCollider(Collider* collider);
	//�����p����
	void RayCollision(Segment* segment, CollisionType type, DirectX::SimpleMath::Vector3* pushback);
private:
	//�Փ˔�������s���邩����
	bool IsAct(int collision1num, int collision2num);
	//�ړ��I�u�W�F�N�g���m
	void Collision(int i, int j);
	//�Œ�I�u�W�F�N�g�ƈړ��I�u�W�F�N�g
	void Fixed_Collision(int i, int j);
	//�ڐG�m�F
	void Trigger(int i, int j);
	
};