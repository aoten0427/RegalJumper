// ================================================================ 
// �t�@�C���� : Target.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �^�[�Q�b�g
// ================================================================
#include"pch.h"
#include"Target.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Component/Collider/Collider.h"
#include"Base/Event/Subject.h"
#include"Base/Event/Observer.h"


int Target::TARGET_ID = 0;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
/// <param name="holder">�����I�u�W�F�N�g</param>
/// <param name="type">�^�[�Q�b�g�^�C�v</param>
Target::Target(Scene* scene, Object* holder, TargetType type):Object(scene)
	,
	m_id{TARGET_ID},
	m_type{ type },
	m_holder{ holder },
	m_isActive{ false },
	m_isTarget{ false }
{
	//ID���Z
	TARGET_ID++;
	//�e�q�ݒ�
	GetTransform()->SetParent(holder->GetTransform());
	//�R���C�_�[����
	m_collider = AddComponent<Sphere>(this, CollisionType::TRIGGER, nullptr,false,3.0f);
	//�j��T�u�W�F�N�g����
	std::string subjectName = "Target" + std::to_string(m_id);
	m_destroySubject = AddComponent<Subject<>>(this, subjectName);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Target::~Target()
{
	//�T�[�`���[�Ɏ��g�������悤�w��
	m_destroySubject->Notify();
}

/// <summary>
/// �͈͓�����
/// </summary>
/// <param name="pos">�T�[�`���[�̈ʒu</param>
/// <param name="dire">�T�[�`���[�̌���</param>
/// <param name="range">�������a</param>
/// <param name="vision">�����p�x</param>
/// <returns>�͈͂ɓ����Ă��邩</returns>
bool Target::IsRange(const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& dire, const float& range, const float& vision)
{
	//�T�[�`���[�Ƃ̋������v�Z
	DirectX::SimpleMath::Vector3 PosToTarget = m_collider->GetTransform().GetWorldPosition() - pos;
	//�T�[�`���[�T���͈͊O�Ȃ�A�N�e�B�u���I�t��
	if (PosToTarget.Length() > range)
	{
		m_isActive = false;
		return false;
	}
	PosToTarget.Normalize();
	//�͈͊p�x�����𔻒f
	if (dire.Dot(PosToTarget) > vision)
	{
		m_isActive = true;
		return true;
	}
	return false;
}

/// <summary>
/// Trigger���s���� �T�[�`���[�̂ݔ��������
/// </summary>
/// <param name="collider">�R���C�_�[</param>
/// <returns>����L��</returns>
bool Target::IsTriggerAct(Collider* collider)
{
	if (collider->GetObject()->GetTag() == ObjectTag::Search)return true;
	return false;
}

/// <summary>
/// �T�[�`���[�̓o�^
/// </summary>
/// <param name="observer"></param>
void Target::SetSearch(Observer<>* observer)
{
	std::string subjectName = "Target" + std::to_string(m_id);
	observer->RegistrationSubject(subjectName);
}

/// <summary>
/// �T�[�`���[�̉���
/// </summary>
/// <param name="observer"></param>
void Target::RemoveSearch(Observer<>* observer)
{
	std::string subjectName = "Target" + std::to_string(m_id);
	observer->RemoveSubject(subjectName);
}
