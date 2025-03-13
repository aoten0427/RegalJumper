// ================================================================ 
// ファイル名 : ThreadStateMachine.cpp
// 作成者 : 景山碧天
// 説明 :  糸の状態を管理
// ================================================================
#include"pch.h"
#include"ThreadStateMachine.h"
#include"Game/Play/Thread/ThreadState/ThreadNone.h"
#include"Game/Play/Thread/ThreadState/ThreadShot.h"
#include"Game/Play/Thread/ThreadState/ThreadCut.h"
#include"Game/Play/Thread/ThreadState/ThreadShrink.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="thread">糸</param>
ThreadStateMachine::ThreadStateMachine(Thread* thread)
{
	AddState(std::make_unique<ThreadNone>(this, thread), ThreadState::State::None);
	AddState(std::make_unique<ThreadShot>(this, thread), ThreadState::State::Shot);
	AddState(std::make_unique<ThreadCut>(this, thread), ThreadState::State::Cut);
	AddState(std::make_unique<ThreadShrink>(this, thread), ThreadState::State::Shrink);

	SetStart(ThreadState::State::None);
}
