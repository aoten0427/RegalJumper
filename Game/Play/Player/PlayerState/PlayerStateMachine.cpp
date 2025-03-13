// ================================================================ 
// ファイル名 : PlayerStateMachine.cpp
// 作成者 : 景山碧天
// 説明 :  プレイヤーの状態を管理
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
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
PlayerStateMachine::PlayerStateMachine(Player* player)
{
	AddState(std::make_unique<PlayerIdle>(this,player),PlayerState::State::IDLE);
	AddState(std::make_unique<PlayerWalk>(this,player), PlayerState::State::WALK);
	AddState(std::make_unique<PlayerShot>(this, player), PlayerState::State::SHOT);
	AddState(std::make_unique<PlayerMoveThread>(this, player), PlayerState::State::MOVETHREAD);
	AddState(std::make_unique<PlayerDamage>(this,player), PlayerState::State::DAMAGE);

	SetStart(PlayerState::State::IDLE);
}
