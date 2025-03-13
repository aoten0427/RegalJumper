// ================================================================ 
// �t�@�C���� :Player.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[
// ================================================================
#include"pch.h"
#include"Player.h"
#include"Base/Base.h"
#include"Base/Event/Observer.h"
#include"Base/Event/Subject.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/PlayerState/PlayerStateMachine.h"
#include"Game/Play/Camera/PlayCamera.h"
#include"Game/Play/Thread/ThreadHolder.h"
#include"Game/Parameter/PlayerParameter.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
/// <param name="center">�v���C���[�Z���^�[</param>
Player::Player(Scene* scene,PlayerCenter* center):Object(scene)
	,
	m_playerCenter{center},
	m_collider{nullptr},
	m_rigidbody{nullptr},
	m_model{nullptr},
	m_stateMachine{nullptr},
	m_isGround{false}
{
	using namespace DirectX::SimpleMath;

	//���W�b�h�{�f�B�쐬
	m_rigidbody = AddComponent<Rigidbody>(this);
	m_rigidbody->SetMass(PlayerParameter::PARAMETER()->MASS);
	//����쐬
	m_collider = AddComponent<OBB>(this, CollisionType::COLLISION, m_rigidbody, false);
	m_collider->SetScale(PlayerParameter::PARAMETER()->COLLIDER_SIZE);
	//���f���쐬
	m_model = scene->AddObject<SpiderModels>(scene, this);
	m_model->ChangeState(SpiderModelState::RenderType::NONE);
	//�X�e�[�g�}�V���쐬
	m_stateMachine = std::make_unique<PlayerStateMachine>(this);
	//�J�����擾
	m_camera = static_cast<PlayCamera*>(GetScene()->GetCamera());
	m_camera->SetPlayer(this);
	//���ۗL�ҋ@�\�쐬
	ThreadHolder* threadholder = AddComponent<ThreadHolder>(this);
	threadholder->SetConect([&]() {m_stateMachine->ChangeState(PlayerState::State::MOVETHREAD); });
	threadholder->SetCut([&]() {m_stateMachine->ChangeState(PlayerState::State::WALK); });
	//���S���T�u�W�F�N�g�쐬
	m_deathSubject = AddComponent<Subject<>>(this, "PlayerDeath");
	//�f�[�^���Z�b�g�I�u�U�[�o�[�쐬
	m_resetObserver = AddComponent<Observer<>>(this);
	m_resetObserver->RegistrationSubject("PlayReset");
	m_resetObserver->SetFunction([&]() {Reset(); });
	//�����ʒu�ݒ�
	GetTransform()->SetPosition(PlayerParameter::PARAMETER()->INITIAL_POSITION);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void Player::ObjectUpdate(float deltatime)
{
	using namespace DirectX::SimpleMath;
	//�v���C��ԈȊO�͓������Ȃ�
	if (GetScene()->GetState() != Scene::State::PLAY)return;

	//��]���J��������擾
	float rotatin = m_camera->GetRotationY();
	//��]
	GetTransform()->SetRotate(Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(rotatin)));
	//�X�e�[�g�}�V���A�b�v�f�[�g
	m_stateMachine->Update(deltatime);

	//�n�㔻��̃��Z�b�g
	m_isGround = false;

	IsDeath();
}

/// <summary>
/// �o������
/// </summary>
void Player::Entery()
{
	m_model->ChangeState(SpiderModelState::RenderType::ENTRY);
}

/// <summary>
/// Trigger���s�L�� �@�S�[���ƃw���v�̂ݔ���
/// </summary>
/// <param name="collider"></param>
/// <returns></returns>
bool Player::IsTriggerAct(Collider* collider)
{
	if (collider->GetObject()->GetTag() == ObjectTag::Goal)return true;
	if (collider->GetObject()->GetTag() == ObjectTag::Help)return true;
	return false;
}

/// <summary>
/// Collision���s�L���@�^�[�Q�b�g�{�b�N�X�͔��肵�Ȃ�
/// </summary>
/// <param name="collider"></param>
/// <returns></returns>
bool Player::IsCollisionAct(Collider* collider)
{
	if (collider->GetObject()->GetTag() == ObjectTag::TargetBox)return false;
	return true;
}

/// <summary>
/// �����o�������@�n�㔻��𔻒�
/// </summary>
/// <param name="pushback">�����o����</param>
void Player::PushBack(DirectX::SimpleMath::Vector3 pushback)
{
	GetTransform()->Translate(pushback);
	//�ウ�̉����o���̏ꍇ�n�ʐڐG�t���O���I���ɂ���
	if (pushback.y > 0)m_isGround = true;
}

/// <summary>
/// Trigger���� �S�[������
/// </summary>
/// <param name="collider"></param>
void Player::OnTrigger(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
	//�S�[���ڐG����
	if (collider->GetObject()->GetTag() == ObjectTag::Goal)
	{
		IsGoal();
	}
}

/// <summary>
/// Collision����
/// </summary>
/// <param name="collider">����</param>
void Player::OnCollision(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
}

bool Player::IsDetectionAct(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
	return false;
}

/// <summary>
/// �f�[�^���Z�b�g
/// </summary>
void Player::Reset()
{
	GetTransform()->SetPosition(PlayerParameter::PARAMETER()->INITIAL_POSITION);
	GetTransform()->SetRotate(DirectX::SimpleMath::Quaternion::Identity);
	GetTransform()->TransRotate(DirectX::SimpleMath::Vector3::UnitY, 180.0f);
}

/// <summary>
/// �S�[������
/// </summary>
void Player::IsGoal()
{
	m_stateMachine->ChangeState(PlayerState::State::IDLE);
	m_stateMachine->ChangeState();

	GetScene()->ChangeState(Scene::State::END);
	m_model->ChangeState(SpiderModelState::RenderType::EXIT);
}

/// <summary>
/// ���S����
/// </summary>
void Player::IsDeath()
{
	if (GetTransform()->GetPosition().y < PlayerParameter::PARAMETER()->RESET_HEIGHT)
	{
		m_deathSubject->Notify();
	}
}
