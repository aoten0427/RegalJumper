// ================================================================ 
// ファイル名 : PlayerState.cpp
// 作成者 : 景山碧天
// 説明 :  プレイヤーの状態を管理
// ================================================================
#include"pch.h"
#include"PlayerIdle.h"
#include"Game/Play/Player/PlayerState/PlayerStateMachine.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">プレイヤーステートマシン</param>
/// <param name="player">プレイヤー</param>
PlayerState::PlayerState(PlayerStateMachine* machine, Player* player)
	:
	m_machine{machine}
{
	UNREFERENCED_PARAMETER(player);
}

/// <summary>
/// 状態変更
/// </summary>
/// <param name="nextstate">次のステート</param>
void PlayerState::ChangeState(State nextstate)
{
	//ステートマシンに状態変更指示
	m_machine->ChangeState(nextstate);
}
