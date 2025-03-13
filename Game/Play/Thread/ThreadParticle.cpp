// ================================================================ 
// �t�@�C���� : ThreadParticle.h
// �쐬�� : �i�R�ɓV
// ���� :  ���̍ŏ��P��
// ================================================================
#include"pch.h"
#include"ThreadParticle.h"
#include"Base/Component/Collider/Collider.h"
#include"Base/Component/Rigidbody/Rigidbody.h"
#include"Game/Play/Thread/Thread.h"
#include"Game/Play/Thread/ThreadState/ThreadStateMachine.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene"></param>
/// <param name="thread"></param>
/// <param name="iscollider"></param>
/// <param name="isdetection"></param>
ThreadParticle::ThreadParticle(Scene* scene, Thread* thread, bool iscollider, bool isdetection):Object(scene)
	,
	m_thread{ thread },
	m_rigidbody{ nullptr },
	m_isTip{ false }
{
	m_rigidbody = AddComponent<Rigidbody>(this);
	m_rigidbody->SetMass(2.0f);

	UNREFERENCED_PARAMETER(isdetection);
	if (iscollider)
	{
		AddComponent<Sphere>(this, CollisionType::COLLISION, m_rigidbody,false, 0.5f);
	}
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime"></param>
void ThreadParticle::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	if (m_thread->GetStateMachine()->GetCurrensState() == ThreadState::State::Shrink)
	{
		m_rigidbody->AddForce(DirectX::SimpleMath::Vector3(0, -1.2f, 0));
	}

	
}

/// <summary>
/// Collision���s�L��
/// </summary>
/// <param name="collider"></param>
/// <returns></returns>
bool ThreadParticle::IsCollisionAct(Collider* collider)
{

	if (collider->GetObject()->GetTag() == ObjectTag::Stage ||
		collider->GetObject()->GetTag() == ObjectTag::TargetBox ||
		collider->GetObject()->GetTag() == ObjectTag::Enemy ||
		collider->GetObject()->GetTag() == ObjectTag::Barrier)return true;

	return false;
}

/// <summary>
/// Collision����
/// </summary>
/// <param name="collider"></param>
void ThreadParticle::OnCollision(Collider* collider)
{
	if ((collider->GetObject()->GetTag() == ObjectTag::Stage ||
		collider->GetObject()->GetTag() == ObjectTag::TargetBox ||
		collider->GetObject()->GetTag() == ObjectTag::Enemy) && m_isTip)
	{
		//�����k�߂�
		m_isTip = false;
		m_thread->GetStateMachine()->ChangeState(ThreadState::State::Shrink);
	}
}

bool ThreadParticle::IsDetectionAct(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
	return false;
}
