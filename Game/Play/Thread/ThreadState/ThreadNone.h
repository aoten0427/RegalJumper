// ================================================================ 
// ファイル名 : 
// 作成者 : 景山碧天
// 説明 :  
// ================================================================

#pragma once
#include"Game/Play/Thread/ThreadState/ThreadState.h"


class ThreadNone :public ThreadState
{
private:
public:
	ThreadNone(ThreadStateMachine* machine, Thread* thread);
	~ThreadNone()override = default;

	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
};