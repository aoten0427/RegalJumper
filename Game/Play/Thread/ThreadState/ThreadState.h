// ================================================================ 
// ファイル名 : ThreadState.h
// 作成者 : 景山碧天
// 説明 :  糸の状態基底クラス
// ================================================================

#pragma once
#include"Base/MyLibraries/StateMachine/IState.h"

class Thread;
class ThreadStateMachine;

class ThreadState :public IState
{
public:
	//状態
	enum class State
	{
		None,
		Shot,
		Shrink,
		Paste,
		Cut,
		Attack
	};
private:
	//ステートマシン
	ThreadStateMachine* m_machine;
public:
	//コンストラクタ
	ThreadState(ThreadStateMachine* machine, Thread* thread);
	//デストラクタ
	virtual ~ThreadState()override = default;
	//状態変化
	void ChangeState(State state);
};