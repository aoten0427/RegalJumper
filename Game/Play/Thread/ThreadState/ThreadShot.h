// ================================================================ 
// ファイル名 : ThreadShot.h
// 作成者 : 景山碧天
// 説明 :  糸発射状態
// ================================================================

#pragma once
#include"Game/Play/Thread/ThreadState/ThreadState.h"
#include"Game/Parameter/ThreadParameter.h"


class ThreadShot :public ThreadState
{
private:
	//糸
	Thread* m_thread;
	//持続時間
	float m_continuationTimer;
	//糸の幅
	float m_distance;
	//パラメータ
	const ThreadParameter::Parameter* m_parameter;
public:
	//コンストラクタ
	ThreadShot(ThreadStateMachine* machine, Thread* thread);
	//デストラクタ
	~ThreadShot()override = default;
	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
private:
	//再加速
	void ReAcceleration();
};