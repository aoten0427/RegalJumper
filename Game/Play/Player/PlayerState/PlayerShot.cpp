// ================================================================ 
// �t�@�C���� : PlayerShot.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[�V���b�g���
// ================================================================
#include"pch.h"
#include"PlayerShot.h"
#include"Base/Base.h"
#include"Base/Sound/Sound.h"
#include"Game/Play/Player/PlayerCenter.h"
#include"Game/Play/Player/Player.h"
#include"MyLib/DebugString.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="machine">�v���C���[�X�e�[�g�}�V��</param>
/// <param name="player">�v���C���[</param>
PlayerShot::PlayerShot(PlayerStateMachine* machine, Player* player) :PlayerState(machine, player)
	,
	m_player{player}
{
	m_commonResources = player->GetCommonResources();
	m_shotSound = m_player->AddComponent<Sound>(m_player, Sound::SoundType::SE, "Shot", false);
}

/// <summary>
/// ���O�X�V
/// </summary>
void PlayerShot::PreUpdate()
{
	//��������
	DirectX::SimpleMath::Vector3 direction = m_player->GetScene()->GetCamera()->GetRayDirection();
	//���ˏ���
	m_player->GetPlayerCenter()->ThreadShot(direction);
	//������炷
	m_shotSound->Play();
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
void PlayerShot::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	ChangeState(State::WALK);
}

/// <summary>
/// ����X�V
/// </summary>
void PlayerShot::PostUpdate()
{
}
