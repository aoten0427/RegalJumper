// ================================================================ 
// �t�@�C���� : PlayerMoveThread.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[���ł̈ړ����
// ================================================================
#include"pch.h"
#include"PlayerMoveThread.h"
#include"Base/Base.h"
#include"Base/Event/Subject.h"
#include"Game/Play/Player/Player.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/SpiderAnimation/SpiderAnimatorCenter.h"
#include"MyLib/DebugString.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">�v���C���[�X�e�[�g�}�V��</param>
/// <param name="player">�v���C���[</param>
PlayerMoveThread::PlayerMoveThread(PlayerStateMachine* machine, Player* player) :PlayerState(machine, player)
	,
	m_player{ player },
	m_conectSubject{nullptr},
	m_parameter{PlayerParameter::PARAMETER()}
{
	m_commonResources = player->GetCommonResources();
	m_input = m_commonResources->GetInput();
	m_playerRigidbody = player->GetComponent<Rigidbody>();
	m_conectSubject = m_player->AddComponent<Subject<>>(m_player, "PlayerThreadConect");
}

/// <summary>
/// ���O�X�V
/// </summary>
void PlayerMoveThread::PreUpdate()
{
	//�A�j���[�^�[�ύX
	SpiderAnimatorCenter* anime = m_player->GetModel()->GetAnimator();
	anime->SetActiveAnimator("PlayerAir",true);
	m_conectSubject->Notify();
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
void PlayerMoveThread::Update(float deltaTime)
{
	using namespace DirectX::SimpleMath;

	//�d��
	m_playerRigidbody->AddForce(Vector3(0, m_parameter->GRAVITY_THREAD * deltaTime, 0));
	//��R
	m_playerRigidbody->AddForce(m_playerRigidbody->GetAddforce() * m_parameter->FRECTION_THREAD);
	Move(deltaTime);
}

/// <summary>
/// ����X�V
/// </summary>
void PlayerMoveThread::PostUpdate()
{
	if (!m_player->GetIsGround())
	{
		//�A�j���[�^�[�ύX
		SpiderAnimatorCenter* anime = m_player->GetModel()->GetAnimator();
		anime->SetActiveAnimator("PlayerAction", true);
	}
}

/// <summary>
/// �ړ�
/// </summary>
/// <param name="deltatime">�t���[���o�ߎ���</param>
void PlayerMoveThread::Move(float deltatime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	if (m_input->IsKeyPress(Keyboard::None))return;
	Transform* transform = m_player->GetTransform();
	//�O��ړ�
	if (m_input->IsKeyDown(Keyboard::W))
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(0, 0, 1)) * -m_parameter->SPEED_THREAD * deltatime);
	}
	if (m_input->IsKeyDown(Keyboard::S))
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(0, 0, 1)) * m_parameter->SPEED_THREAD * deltatime);
	}
	//�W�����v
	if (m_input->IsKeyPress(Keyboard::Space) && m_player->GetIsGround())
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(0, 1, 0)) * m_parameter->JUMP_POWER);
	}
}
