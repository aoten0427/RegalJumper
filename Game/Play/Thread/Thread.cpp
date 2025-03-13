// ================================================================ 
// ファイル名 : Thread.h
// 作成者 : 景山碧天
// 説明 :  糸
// ================================================================
#include"pch.h"
#include"Thread.h"
#include"Base/Base.h"
#include"Game/Play/Thread/ThreadState/ThreadStateMachine.h"
#include"Game/Play/Thread/ThreadParticle.h"
#include"Game/Play/Thread/RopeSolver.h"
#include"Game/Play/Thread/ThreadModel.h"
#include"Game/Play/Thread/ThreadHolder.h"
#include"Game/Play/Enemy/Target.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene"></param>
Thread::Thread(Scene* scene):Object(scene)
	, m_ropeSolver{},
	m_threadparticles{},
	m_data{},
	m_ropeDistance{ 5.0f }
{
	//ステートマシン作成
	m_machine = std::make_unique<ThreadStateMachine>(this);
	//ロープソルバー作成
	m_ropeSolver = AddComponent<RopeSolver>(this);
	//モデル作成
	scene->AddObject<ThreadModel>(scene, this);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime"></param>
void Thread::ObjectUpdate(float deltatime)
{
	m_machine->Update(deltatime);
}

/// <summary>
/// 発射
/// </summary>
/// <param name="holder">保持者</param>
/// <param name="position">発射位置</param>
/// <param name="direction">発射方向</param>
/// <param name="target">ターゲット</param>
void Thread::Shot(Object* holder, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 direction, Target* target)
{
	//データをセット
	m_data.m_holder = holder;
	m_data.m_threadHolder = holder->GetComponent<ThreadHolder>();
	m_data.m_startPosition = position;
	m_data.m_direction = direction;
	m_data.m_target = target;
	if (!m_data.m_threadHolder)return;

	//ロープをアクティブに
	m_ropeSolver->SetActive(true);

	//ターゲットが指定されている場合はそちらに発射する
	if (target)
	{
		m_data.m_direction = target->GetTransform()->GetWorldPosition() - position;
		m_data.m_direction.Normalize();
	}

	m_machine->ChangeState(ThreadState::State::Shot);
}

/// <summary>
/// データクリア
/// </summary>
void Thread::Clear()
{
	for (auto& particle : m_threadparticles)
	{
		particle->Destroy();
	}
	m_threadparticles.clear();
	m_ropeSolver->SetActive(false);
	m_ropeSolver->Clear();
}
