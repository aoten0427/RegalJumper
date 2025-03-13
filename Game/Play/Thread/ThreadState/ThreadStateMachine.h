// ================================================================ 
// ファイル名 : ThreadStateMachine.h
// 作成者 : 景山碧天
// 説明 :  糸の状態を管理
// ================================================================
#pragma once
#include"Base/MyLibraries/StateMachine/StateMachine.h"
#include"Game/Play/Thread/ThreadState/ThreadState.h"

class Thread;

class ThreadStateMachine:public StateMachine<ThreadState,ThreadState::State>
{
private:
public:
	//コンストラクタ
	ThreadStateMachine(Thread* thread);
};