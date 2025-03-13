// ================================================================ 
// ファイル名 : PlayerStateMachine.h
// 作成者 : 景山碧天
// 説明 :  プレイヤーの状態を管理
// ================================================================

#pragma once
#include"Base/MyLibraries/StateMachine/StateMachine.h"
#include"Game/Play/Player/PlayerState/PlayerState.h"

class Player;

class PlayerStateMachine :public StateMachine<PlayerState,PlayerState::State>
{
private:
public:
	PlayerStateMachine(Player* player);
};