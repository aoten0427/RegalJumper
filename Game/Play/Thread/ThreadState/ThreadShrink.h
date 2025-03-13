// ================================================================ 
// ファイル名 : ThreadShrink.h
// 作成者 : 景山碧天
// 説明 :  糸が縮む状態
// ================================================================

#pragma once
#include"Game/Play/Thread/ThreadState/ThreadState.h"
#include"Game/Parameter/ThreadParameter.h"

class DirectXInputs;

class ThreadShrink :public ThreadState
{
private:
	//糸
	Thread* m_thread;
	//糸の幅
	float m_initialDistance;
	//幅を減らす量
	float m_shrinkValue;
	//変化割合
	float m_ratio;
	//パラメータ
	const ThreadParameter::Parameter* m_parameter;
	//変化量
	float m_changeValue;
	//変化イージング
	std::string m_easingtype;
	//入力機構
	DirectXInputs* m_input;

	
public:
	//コンストラクタ
	ThreadShrink(ThreadStateMachine* machine, Thread* thread);
	//デストラクタ
	~ThreadShrink()override = default;
	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
};