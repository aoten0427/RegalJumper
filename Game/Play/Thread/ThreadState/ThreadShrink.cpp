// ================================================================ 
// ファイル名 : ThreadShrink.cpp
// 作成者 : 景山碧天
// 説明 :  糸が縮む状態
// ================================================================
#include"pch.h"
#include"ThreadShrink.h"
#include"Base/Base.h"
#include"Game/Play/Thread/Thread.h"
#include"Game/Play/Thread/ThreadParticle.h"
#include"Game/Play/Thread/RopeSolver.h"
#include"Game/Play/Thread/Constraint.h"
#include"Game/Play/Thread/Particle.h"
#include"Game/Play/Thread/ThreadHolder.h"
#include"Base/Tween/DoTween.h"

constexpr float SHRINK_MIN = 0.01f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">糸ステートマシン</param>
/// <param name="thread">糸</param>
ThreadShrink::ThreadShrink(ThreadStateMachine* machine, Thread* thread) :ThreadState(machine, thread)
	,
	m_thread{thread},
	m_initialDistance{ 0 },
	m_shrinkValue{ 0 },
	m_ratio{0},
	m_parameter{ThreadParameter::PARAMETER()},
	m_changeValue{0}
{
	m_input = thread->GetCommonResources()->GetInput();
}

/// <summary>
/// 事前更新
/// </summary>
void ThreadShrink::PreUpdate()
{
	using namespace DirectX::SimpleMath;

	//データのリセット
	m_initialDistance = 0;
	m_shrinkValue = m_parameter->SHRINK_VALUE_BEGIN;
	m_changeValue = m_parameter->SHRINK_VALUE_BEGIN - m_parameter->SHRINK_VALUE_END;
	m_easingtype = m_parameter->SHRINK_EASING;

	//データ取得
	Thread::ThreadData data = m_thread->GetData();
	//パーティクルの取得
	std::vector<ThreadParticle*> threadParticle = m_thread->GetThreadParticles();
	//ホルダ-への糸の影響をありにする
	Particle* holderParticle = data.m_holder->GetComponent<Particle>();
	if (holderParticle == nullptr)return;
	holderParticle->SetIsMove(true);

	//端を固定
	threadParticle.back()->GetRigidbody()->SetFixed(true);
	//スピードをリセット
	for (auto& particle : threadParticle)
	{
		particle->GetRigidbody()->SetAddForce(Vector3::Zero);
		particle->GetRigidbody()->SetMass(1.0f);
	}
	//制約距離の調整
	Vector3 begin = threadParticle.front()->GetTransform()->GetWorldPosition();
	Vector3 end = threadParticle.back()->GetTransform()->GetWorldPosition();
	float lenth = Vector3::Distance(begin, end);
	float distance = lenth / (threadParticle.size()) * 0.9f;
	//ロープソルバーに情報を設定
	m_thread->GetRopeSolver()->SetFlexibility(0.0001f);
	m_initialDistance = distance;
	m_thread->GetRopeSolver()->SetDistance(m_initialDistance);
	//Conect通知
	data.m_threadHolder->Conect();

	m_thread->SetThreadParticle(threadParticle);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
void ThreadShrink::Update(float deltaTime)
{
	//変化割合を調整
	m_ratio += deltaTime * m_parameter->SHRINK_SPEED;
	if (m_ratio > 1)m_ratio = 0;
	//縮ませる量を変化
	m_shrinkValue = (1 - Easing::Selection(Easing::GetEase(m_easingtype), m_ratio)) * m_changeValue + m_parameter->SHRINK_VALUE_END;
	//糸の幅を縮ませる
	m_initialDistance -= deltaTime * m_shrinkValue;
	if (m_initialDistance <= SHRINK_MIN)m_initialDistance = SHRINK_MIN;
	//糸の幅を設定
	m_thread->GetRopeSolver()->SetDistance(m_initialDistance);

	//左マウスが離されたら糸を切る
	if (m_input->GetMouseTracker()->leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::UP)
	{
		ChangeState(State::Cut);
	}
}

/// <summary>
/// 事後更新
/// </summary>
void ThreadShrink::PostUpdate()
{
}
