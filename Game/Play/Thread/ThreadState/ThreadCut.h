// ================================================================ 
// ファイル名 : ThreadCut.h
// 作成者 : 景山碧天
// 説明 :  糸が切れる状態
// ================================================================

#pragma once
#include"Game/Play/Thread/ThreadState/ThreadState.h"


class ThreadCut :public ThreadState
{
private:
	//糸
	Thread* m_thread;
public:
	//コンストラクタ
	ThreadCut(ThreadStateMachine* machine, Thread* thread);
	//デストラクタ
	~ThreadCut()override = default;
	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
};