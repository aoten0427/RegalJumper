// ================================================================ 
// �t�@�C���� : CollisionManager.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �Փ˔�����Ǘ�
// ================================================================

#include"pch.h"
#include"CollisonManager.h"
#include"Base/Component/Collider/Collision.h"
#include"Base/Object/Object.h"
#include"Base/Component/Rigidbody/Rigidbody.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CollisionManager::CollisionManager()
{
}


/// <summary>
/// �A�b�v�f�[�g�@�Փ˔�������s
/// </summary>
void CollisionManager::Update()
{
	for (int i = 0; i < m_collisionDates.size(); i++)
	{
		for (int j = i + 1; j < m_collisionDates.size(); j++)
		{
			//�Փ˔�������s���邩���f
			if (!IsAct(i, j))continue;

			//�Œ�I�u�W�F�N�g�ƈړ��I�u�W�F�N�g
			if (m_collisionDates[i].m_type == CollisionType::FIXED && m_collisionDates[j].m_type == CollisionType::COLLISION)
			{
				Fixed_Collision(i, j);
			}
			if (m_collisionDates[i].m_type == CollisionType::FIXED && m_collisionDates[j].m_type == CollisionType::TRIGGER)
			{
				Trigger(i, j);
			}
			//�ړ��I�u�W�F�N�g�ƈړ��I�u�W�F�N�g
			else if(m_collisionDates[i].m_type == CollisionType::COLLISION && m_collisionDates[j].m_type == CollisionType::COLLISION)
			{
				Collision(i, j);
			}
			//�ړ��I�u�W�F�N�g�Ƃ��蔲���I�u�W�F�N�g
			else if (m_collisionDates[i].m_type == CollisionType::COLLISION && m_collisionDates[j].m_type == CollisionType::TRIGGER)
			{
				Trigger(i, j);
			}
			//���蔲���I�u�W�F�N�g�Ƃ��蔲���I�u�W�F�N�g
			else if (m_collisionDates[i].m_type == CollisionType::TRIGGER && m_collisionDates[j].m_type == CollisionType::TRIGGER)
			{
				Trigger(i, j);
			}
		}
	}
}

/// <summary>
/// �R���C�_�[�ǉ�
/// </summary>
/// <param name="collider"></param>
/// <param name="type"></param>
void CollisionManager::AddCollider(Collider* collider, CollisionType type)
{
	//�O�ՋN���p�̓p�X
	if (type == CollisionType::ORBIT)return;

	//�V�����R���C�_�[�f�[�^����蒆�g��ݒ�
	CollisionData newdata{
		collider->GetObject(),
		collider,
		collider->GetRigidbody(),
		type
	};

	m_collisionDates.push_back(newdata);

	//����̃^�C�v���Ƃɕ��ёւ�
	std::sort(m_collisionDates.begin(), m_collisionDates.end(), [](CollisionData& data1, CollisionData& data2) {
		return (int)data1.m_type < (int)data2.m_type;
		});
}

/// <summary>
/// �R���C�_�[�폜
/// </summary>
/// <param name="collider"></param>
void CollisionManager::ReMoveCollider(Collider* collider)
{

	auto itr = std::find_if(m_collisionDates.begin(), m_collisionDates.end(), [&, collider]
	(const CollisionData& collisiondata) {
			return collisiondata.m_collider == collider;
		});

	if (itr != m_collisionDates.end())
	{
		m_collisionDates.erase(itr);
	}
}


/// <summary>
/// �Փ˔�������s���邩����
/// </summary>
/// <param name="collision1num">����1</param>
/// <param name="collision2num">����2</param>
/// <returns>���s�L��</returns>
bool CollisionManager::IsAct(int collision1num, int collision2num)
{
	//�T�C�Y�O���p�X
	if (collision2num >= m_collisionDates.size())return false;
	//��A�N�e�B�u��ԂȂ�p�X
	if (!m_collisionDates[collision1num].m_collider->GetActive())return false;
	if (!m_collisionDates[collision2num].m_collider->GetActive())return false;
	//���I�u�W�F�N�g�Ȃ�p�X
	if (m_collisionDates[collision1num].m_holder == m_collisionDates[collision2num].m_holder)return false;
	//���ꂼ�ꃊ�W�b�h�{�f�B���Ȃ���΃p�X
	if (m_collisionDates[collision1num].m_rigidbody == nullptr && m_collisionDates[collision2num].m_rigidbody == nullptr)return false;
	//�����Œ�I�u�W�F�N�g�Ȃ�p�X
	if (m_collisionDates[collision1num].m_type == CollisionType::FIXED && m_collisionDates[collision2num].m_type == CollisionType::FIXED)return false;

	return true;
}

/// <summary>
/// Collision���m
/// </summary>
/// <param name="i">����1</param>
/// <param name="j">����2</param>
void CollisionManager::Collision(int i, int j)
{
	using namespace DirectX::SimpleMath;

	//������Ƃ�Ȃ��Ȃ�p�X
	if (!m_collisionDates[i].m_holder->IsCollisionAct(m_collisionDates[j].m_collider))return;
	if (!m_collisionDates[j].m_holder->IsCollisionAct(m_collisionDates[i].m_collider))return;

	//�߂荞�ݗʂ��v�Z
	Vector3 pushback = Collision::OnCollision(*m_collisionDates[i].m_collider, *m_collisionDates[j].m_collider);
	//�߂荞�݂��Ȃ��Ȃ�p�X
	if (pushback.Length() == 0)return;

	//�o���̏d�����l�����Ĉړ��ʂ��v�Z
	float addmass = m_collisionDates[i].m_rigidbody->GetMass() + m_collisionDates[j].m_rigidbody->GetMass();
	m_collisionDates[i].m_holder->PushBack(pushback * (1 - (m_collisionDates[i].m_rigidbody->GetMass() / addmass)));
	m_collisionDates[j].m_holder->PushBack(-pushback * (1 - (m_collisionDates[j].m_rigidbody->GetMass() / addmass)));
}

/// <summary>
/// Fixed��Collision
/// </summary>
/// <param name="i">����1</param>
/// <param name="j">����2</param>
void CollisionManager::Fixed_Collision(int i, int j)
{
	using namespace DirectX::SimpleMath;

	//������Ƃ�Ȃ��Ȃ�p�X
	if (!m_collisionDates[i].m_holder->IsCollisionAct(m_collisionDates[j].m_collider))return;
	if (!m_collisionDates[j].m_holder->IsCollisionAct(m_collisionDates[i].m_collider))return;

	//�߂荞�ݗʂ��v�Z
	Vector3 pushback = Collision::OnCollision(*m_collisionDates[i].m_collider, *m_collisionDates[j].m_collider);
	//�߂荞�݂��Ȃ��Ȃ�p�X
	if (pushback.Length() == 0)return;

	m_collisionDates[j].m_holder->PushBack(-pushback);
	m_collisionDates[i].m_holder->OnCollision(m_collisionDates[j].m_collider);
	m_collisionDates[j].m_holder->OnCollision(m_collisionDates[i].m_collider);
}

/// <summary>
/// Trigger
/// </summary>
/// <param name="i">����1</param>
/// <param name="j">����2</param>
void CollisionManager::Trigger(int i, int j)
{
	using namespace DirectX::SimpleMath;

	//������Ƃ�Ȃ��Ȃ�p�X
	if (!m_collisionDates[i].m_holder->IsTriggerAct(m_collisionDates[j].m_collider))return;
	if (!m_collisionDates[j].m_holder->IsTriggerAct(m_collisionDates[i].m_collider))return;

	//�Փ˗L���𔻒�
	bool hit = Collision::OnTrigger(*m_collisionDates[i].m_collider, *m_collisionDates[j].m_collider);

	if (!hit)return;
	m_collisionDates[i].m_holder->OnTrigger(m_collisionDates[j].m_collider);
	m_collisionDates[j].m_holder->OnTrigger(m_collisionDates[i].m_collider);
}

/// <summary>
/// �X�e�[�W�Ɛ����Ƃ̓����蔻������
/// </summary>
/// <param name="segment">����</param>
/// <param name="type">����^�C�v</param>
/// <param name="pushback">�߂���</param>
void CollisionManager::RayCollision(Segment* segment, CollisionType type, DirectX::SimpleMath::Vector3* pushback)
{
	using namespace DirectX::SimpleMath;

	for (int i = 0; i < m_collisionDates.size(); i++)
	{
		if (m_collisionDates[i].m_type != CollisionType::FIXED)continue;
		if (m_collisionDates[i].m_holder->GetTag() != ObjectTag::Stage)continue;

		if (type == CollisionType::COLLISION)
		{
			//�߂荞�ݗʂ��v�Z
			Vector3 push = Collision::OnCollision(*m_collisionDates[i].m_collider, *segment);
			//�߂荞�݂��Ȃ��Ȃ�p�X
			if (push.Length() == 0)continue;
			*pushback = push;
		}
	}
}


