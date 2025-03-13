// ================================================================ 
// �t�@�C���� : PlayerStateMachine.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[�̏�Ԃ��Ǘ�
// ================================================================
#include"pch.h"
#include"PlayerStateMachine.h"
#include"Game/Play/Player/Player.h"
#include"Game/Play/Player/PlayerState/PlayerIdle.h"
#include"Game/Play/Player/PlayerState/PlayerWalk.h"
#include"Game/Play/Player/PlayerState/PlayerShot.h"
#include"Game/Play/Player/PlayerState/PlayerMoveThread.h"
#include"Game/Play/Player/PlayerState/PlayerDamage.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[</param>
PlayerStateMachine::PlayerStateMachine(Player* player)
{
	AddState(std::make_unique<PlayerIdle>(this,player),PlayerState::State::IDLE);
	AddState(std::make_unique<PlayerWalk>(this,player), PlayerState::State::WALK);
	AddState(std::make_unique<PlayerShot>(this, player), PlayerState::State::SHOT);
	AddState(std::make_unique<PlayerMoveThread>(this, player), PlayerState::State::MOVETHREAD);
	AddState(std::make_unique<PlayerDamage>(this,player), PlayerState::State::DAMAGE);

	SetStart(PlayerState::State::IDLE);
}
