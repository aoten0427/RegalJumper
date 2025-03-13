// ================================================================ 
// �t�@�C���� : Search.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �^�[�Q�b�g��T���T�[�`���[
// ================================================================
#include"pch.h"
#include"Search.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Component/Collider/Collider.h"
#include"Base/Component/Rigidbody/Rigidbody.h"
#include"Base/Event/Observer.h"

#include"Base/Scene/Scene.h"
#include"Base/Camera/Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
/// <param name="holder">�����I�u�W�F�N�g</param>
/// <param name="radius">���a</param>
Search::Search(Scene* scene,Object* holder, float radius):Object(scene)
	,
	m_target{ nullptr },
	m_searchType{ {Target::TargetType::Attack,false},
		{Target::TargetType::Move,false},
		{Target::TargetType::Player,false }
	},
	m_viewingDirection{ DirectX::SimpleMath::Vector3::Zero },
	m_range{ radius },
	m_vision{ 0.95f }
{
	//�e�q�ݒ�
	GetTransform()->SetParent(holder->GetTransform());
	//����쐬(������Ƃ邽�߂̃��W�b�h�{�f�B���쐬)
	Rigidbody* rigidbody = AddComponent<Rigidbody>(this);
	AddComponent<Sphere>(this, CollisionType::TRIGGER,rigidbody,false, m_range);
	//�I�u�U�[�o�[�쐬
	m_targetDelete = AddComponent<Observer<>>(this);
	m_targetDelete->SetFunction([&]() {m_target = nullptr; });
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Search::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	if (m_target != nullptr)
	{
		//�͈͓�����
		if (!m_target->IsRange(GetScene()->GetCamera()->GetEyePosition(),
			m_viewingDirection, m_range, m_vision))
		{
			//�o�^����
			m_target->SetIsTarget(false);
			m_target->RemoveSearch(m_targetDelete);
			m_target = nullptr;
		}
	}
}

/// <summary>
/// Trigger���s�L�� �^�[�Q�b�g�̂ݔ���
/// </summary>
/// <param name="collider">����</param>
/// <returns>����L��</returns>
bool Search::IsTriggerAct(Collider* collider)
{
	//�^�[�Q�b�g�ȊO�̓p�X
	if (collider->GetObject()->GetTag() == ObjectTag::Target)return true;
	return false;
}

/// <summary>
/// Trigger����
/// </summary>
/// <param name="collider">����</param>
void Search::OnTrigger(Collider* collider)
{
	using namespace DirectX::SimpleMath;
	if (collider->GetObject()->GetTag() == ObjectTag::Target)
	{
		//�^�[�Q�b�g�ɕϊ�
		Target* target = dynamic_cast<Target*>(collider->GetObject());
		//�͈͊O�Ȃ�Ԃ�
		if (!target->IsRange(GetScene()->GetCamera()->GetEyePosition(),
			m_viewingDirection, m_range, m_vision))return;
		
		//���݂̂Ɠ���Ȃ�p�X
		if (m_target == target)return;
		
		//�^�[�Q�b�g�ɐݒ�
		if (m_target == nullptr)
		{
			m_target = target;
			m_target->SetIsTarget(true);
			m_target->SetSearch(m_targetDelete);
		}
		else//���݃^�[�Q�b�g������ꍇ
		{
			SelectTarget(target);
		}
		
	}
}

/// <summary>
/// �^�[�Q�b�g��I��
/// </summary>
/// <param name="newTarget">�V�����^�[�Q�b�g</param>
void Search::SelectTarget(Target* newTarget)
{
	using namespace DirectX::SimpleMath;
	//��̃^�[�Q�b�g�̋��������ċ߂��ق���I������
	float dire1 = Vector3::Distance(GetTransform()->GetPosition(), m_target->GetTransform()->GetWorldPosition());
	float dire2 = Vector3::Distance(GetTransform()->GetPosition(), newTarget->GetTransform()->GetWorldPosition());
	if (dire1 > dire2)
	{
		//�o�^����
		m_target->SetIsTarget(false);
		m_target->RemoveSearch(m_targetDelete);
		//�o�^
		m_target = newTarget;
		m_target->SetIsTarget(true);
		m_target->SetSearch(m_targetDelete);
	}
}


