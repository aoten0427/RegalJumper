// ================================================================ 
// �t�@�C���� : PlayerIdle.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[�ҋ@���
// ================================================================
#include"pch.h"
#include"PlayerIdle.h"
#include"Base/Base.h"
#include"Game/Play/Player/Player.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/SpiderAnimation/SpiderAnimatorCenter.h"
#include"MyLib/DebugString.h"
#include"Game/Parameter/PlayerParameter.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">�v���C���[�X�e�[�g�}�V��</param>
/// <param name="player">�v���C���[</param>
PlayerIdle::PlayerIdle(PlayerStateMachine* machine, Player* player) :PlayerState(machine, player)
	,
	m_player{player},
	m_parameter{PlayerParameter::PARAMETER()}
{
	m_commonResources = player->GetCommonResources();
	m_input = m_commonResources->GetInput();
	m_playerRigidbody = player->GetComponent<Rigidbody>();
}

/// <summary>
/// ���O�X�V
/// </summary>
void PlayerIdle::PreUpdate()
{
	//�A�j���[�^�[�ύX
	SpiderAnimatorCenter* anime = m_player->GetModel()->GetAnimator();
	anime->SetActiveAnimator("PlayerIdle",true);
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
void PlayerIdle::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	//�d�͉��Z
	m_playerRigidbody->AddForce(DirectX::SimpleMath::Vector3(0, m_parameter->GRAVITY_GROUND * deltaTime, 0));
	//��R�v�Z
	float fraction = m_player->GetIsGround() ? m_parameter->FRECTION_GROUND : m_parameter->FRECTION_AIR;
	m_playerRigidbody->AddForce(m_playerRigidbody->GetAddforce() * fraction);
	//����m�F
	Operation();
	//������
	Shot();
}

/// <summary>
/// ����X�V
/// </summary>
void PlayerIdle::PostUpdate()
{
}

/// <summary>
/// �ړ��w����t
/// </summary>
void PlayerIdle::Operation()
{
	using namespace DirectX;
	if (m_input->IsKeyPress(Keyboard::None))return;
	//�ړ��w��
	if (m_input->IsKeyPress(Keyboard::W) || m_input->IsKeyPress(Keyboard::S) ||
		m_input->IsKeyPress(Keyboard::A) || m_input->IsKeyPress(Keyboard::D))
	{
		ChangeState(State::WALK);
	}
	//�W�����v
	if (m_input->IsKeyPress(Keyboard::Space) && m_player->GetIsGround())
	{
		m_playerRigidbody->AddForce(m_player->GetTransform()->GetWorldAxisFromLocal(DirectX::SimpleMath::Vector3(0, 1, 0)) * m_parameter->JUMP_POWER);
		ChangeState(State::WALK);
	}
}

/// <summary>
/// ����
/// </summary>
void PlayerIdle::Shot()
{
	if (m_input->GetMouseTracker()->leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		ChangeState(State::SHOT);
	}
}
