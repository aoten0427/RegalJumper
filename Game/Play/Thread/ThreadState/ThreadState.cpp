// ================================================================ 
// ファイル名 : ThreadState.cpp
// 作成者 : 景山碧天
// 説明 :  糸の状態基底クラス
// ================================================================
#include"pch.h"
#include"ThreadState.h"
#include"Game/Play/Thread/ThreadState/ThreadStateMachine.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">糸ステートマシン</param>
/// <param name="thread">糸</param>
ThreadState::ThreadState(ThreadStateMachine* machine, Thread* thread)
	:
	m_machine{machine}
{
	UNREFERENCED_PARAMETER(thread);
}

/// <summary>
/// 状態変化
/// </summary>
/// <param name="state">変更ステート</param>
void ThreadState::ChangeState(State state)
{
	m_machine->ChangeState(state);
}
