// ================================================================ 
// ファイル名 : ThreadCut.cpp
// 作成者 : 景山碧天
// 説明 :  糸が切れる状態
// ================================================================
#include"pch.h"
#include"ThreadCut.h"
#include"Game/Play/Thread/Thread.h"
#include"Game/Play/Thread/ThreadHolder.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">糸ステートマシン</param>
/// <param name="thread">糸</param>
ThreadCut::ThreadCut(ThreadStateMachine* machine, Thread* thread) :ThreadState(machine, thread)
	,
	m_thread{thread}
{
}

/// <summary>
/// 事前更新
/// </summary>
void ThreadCut::PreUpdate()
{
	//カット通知
	m_thread->GetData().m_threadHolder->Cut();
	//糸にクリア処理
	m_thread->Clear();
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
void ThreadCut::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/// <summary>
/// 事後更新
/// </summary>
void ThreadCut::PostUpdate()
{
}
