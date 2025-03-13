// ================================================================ 
// ファイル名 : PlayerState.h
// 作成者 : 景山碧天
// 説明 :  プレイヤーの状態を管理
// ================================================================
#pragma once
#include"Base/MyLibraries/StateMachine/IState.h"

class Player;
class PlayerStateMachine;


class PlayerState :public IState
{
public:
	enum class State
	{
		IDLE,
		WALK,
		SHOT,
		MOVETHREAD,
		DAMAGE,
	};
private:
	//ステートマシン
	PlayerStateMachine* m_machine;
public:
	//コンストラクタ
	PlayerState(PlayerStateMachine* machine, Player* player);
	//デストラクタ
	virtual ~PlayerState() = default;
	//状態変更
	void ChangeState(State nextstate);
};