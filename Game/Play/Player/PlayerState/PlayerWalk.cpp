// ================================================================ 
// �t�@�C���� : PlayerWalk.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[���s���
// ================================================================
#include"pch.h"
#include"PlayerWalk.h"
#include"Base/Base.h"
#include"Game/Play/Player/Player.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/SpiderAnimation/SpiderAnimatorCenter.h"
#include"MyLib/DebugString.h"

constexpr float MIN_SPEED = 0.1f;//�ҋ@��Ԃɖ߂��X�s�[�h�l

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">�v���C���[�X�e�[�g�}�V��</param>
/// <param name="player">�v���C���[</param>
PlayerWalk::PlayerWalk(PlayerStateMachine* machine, Player* player) :PlayerState(machine, player)
	,
	m_player{player},
	m_oldIsGraound{false},
	m_parameter{ PlayerParameter::PARAMETER() }
{
	m_commonResources = player->GetCommonResources();
	m_input = m_commonResources->GetInput();
	m_playerRigidbody = player->GetComponent<Rigidbody>();
}

/// <summary>
/// ���O�X�V
/// </summary>
void PlayerWalk::PreUpdate()
{
	//�A�j���[�^�[�ύX
	SpiderAnimatorCenter* anime = m_player->GetModel()->GetAnimator();
	if (m_player->GetIsGround())
	{
		anime->SetActiveAnimator("PlayerWalk",true);
	}
	else
	{
		anime->SetActiveAnimator("PlayerAir",true);
	}
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
void PlayerWalk::Update(float deltaTime)
{
	

	//�d�͉��Z
	float gravity = m_player->GetIsGround() ? m_parameter->GRAVITY_GROUND : m_parameter->GRAVITY_AIR;
	m_playerRigidbody->AddForce(DirectX::SimpleMath::Vector3(0, gravity * deltaTime, 0));
	//�ړ�
	Move(deltaTime);
	//��R���v�Z
	float frection = m_player->GetIsGround() ? m_parameter->FRECTION_GROUND : m_parameter->FRECTION_AIR;
	m_playerRigidbody->AddForce(m_playerRigidbody->GetAddforce() * frection);
	//������
	Shot();

	//�A�j���[�^�[����
	if (m_player->GetIsGround() != m_oldIsGraound)
	{
		//�A�j���[�^�[�ύX
		SpiderAnimatorCenter* anime = m_player->GetModel()->GetAnimator();
		if (m_player->GetIsGround())
		{
			anime->SetActiveAnimator("PlayerWalk", true);
		}
		else
		{
			anime->SetActiveAnimator("PlayerAir", true);
		}
	}
	

	m_oldIsGraound = m_player->GetIsGround();
}

/// <summary>
/// ����X�V
/// </summary>
void PlayerWalk::PostUpdate()
{
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void PlayerWalk::Move(float deltatime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	if (m_input->IsKeyPress(Keyboard::None))return;
	//���Z�X�s�[�h
	float speed = m_player->GetIsGround() ? m_parameter->SPEED_GROUND : m_parameter->SPEED_AIR;
	bool action = false;

	Transform* transform = m_player->GetTransform();
	//�O�㍶�E�ړ�
	if (m_input->IsKeyDown(Keyboard::W))
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(0, 0, 1)) * -speed * deltatime);
		action = true;
	}
	if (m_input->IsKeyDown(Keyboard::S))
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(0, 0, 1)) * speed * deltatime);
		action = true;
	}
	if (m_input->IsKeyDown(Keyboard::A))
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(1, 0, 0)) * -speed * deltatime);
		action = true;
	}
	if (m_input->IsKeyDown(Keyboard::D))
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(1, 0, 0)) * speed * deltatime);
		action = true;
	}
	//�W�����v
	if (m_input->IsKeyPress(Keyboard::Space)&& m_player->GetIsGround())
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(0, 1, 0)) * m_parameter->JUMP_POWER);
		action = true;
	}


	if (action)return;
	if (!m_player->GetIsGround())return;

	//�X�s�[�h�x�����ȉ��őҋ@��Ԃɖ߂�
	if (abs(m_playerRigidbody->GetVelocity().x) < MIN_SPEED && abs(m_playerRigidbody->GetVelocity().z) < MIN_SPEED)ChangeState(State::IDLE);
}

/// <summary>
/// ���ˏ���
/// </summary>
void PlayerWalk::Shot()
{
	if (m_input->GetMouseTracker()->leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		ChangeState(State::SHOT);
	}
}
