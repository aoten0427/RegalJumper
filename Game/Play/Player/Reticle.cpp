#include"pch.h"
#include"Reticle.h"
#include"Base/Base.h"
#include"Base/Camera/Camera.h"
#include"Game/Play/Player/Player.h"
#include"Base/Event/Subject.h"

constexpr float LENTH = 195;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
/// <param name="player">�v���C���[</param>
Reticle::Reticle(Scene* scene, Player* player):Object(scene)
	,
	m_player{player},
	m_caemra{scene->GetCamera()},
	m_ishit{false},
	m_oldhit{false}
{
	Rigidbody* rigidobyd = AddComponent<Rigidbody>(this);
	//������쐬
	m_segment = AddComponent<Segment>(this, CollisionType::TRIGGER, rigidobyd, false);
	//�T�u�W�F�N�g�쐬
	m_subject = AddComponent<Subject<bool>>(this, "Reticle");
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Reticle::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	using namespace DirectX::SimpleMath;
	//�v���C���[�̈ʒu�ɍ��킹��
	GetTransform()->SetPosition(m_player->GetTransform()->GetPosition());
	//����̌������J�����̌����Ă�������ɍ��킹��
	Vector3 dire = m_caemra->GetTargetPosition() - m_caemra->GetEyePosition();
	dire.Normalize();
	m_segment->SetEndPos(dire * LENTH);

	//�O�t���[�����瓖��������Ԃ��ς�����ꍇ�ʒm
	if (m_oldhit != m_ishit)
	{
		m_subject->Notify(m_ishit);
	}
	//���Z�b�g
	m_oldhit = m_ishit;
	m_ishit = false;

}

/// <summary>
/// Trigger�̎��s�L�� �X�e�[�W�Ɠ������������ׂ�
/// </summary>
/// <param name="collider"></param>
/// <returns></returns>
bool Reticle::IsTriggerAct(Collider* collider)
{
	if (collider->GetObject()->GetTag() == ObjectTag::Stage)return true;
	return false;
}

/// <summary>
/// Trigger����
/// </summary>
/// <param name="collider"></param>
void Reticle::OnTrigger(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
	m_ishit = true;
}
