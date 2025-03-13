// ================================================================ 
// ファイル名 : ThreadShot.cpp
// 作成者 : 景山碧天
// 説明 :  糸発射状態
// ================================================================
#include"pch.h"
#include"ThreadShot.h"
#include"Base/Base.h"
#include"Game/Play/Thread/Thread.h"
#include"Game/Play/Thread/ThreadParticle.h"
#include"Game/Play/Thread/RopeSolver.h"
#include"Game/Play/Thread/Constraint.h"
#include"Game/Play/Thread/Particle.h"
#include"Game/Play/Enemy/Target.h"

//生成パーティクル数
constexpr int PARTICLE_NUM = 30;
//初期距離
constexpr float INITIAL_DISTANCE = 0.2f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">糸ステートマシン</param>
/// <param name="thread">糸</param>
ThreadShot::ThreadShot(ThreadStateMachine* machine, Thread* thread):ThreadState(machine,thread)
	,
	m_thread{thread},
	m_continuationTimer{},
	m_distance{INITIAL_DISTANCE},
	m_parameter{ThreadParameter::PARAMETER()}
{
	
}

/// <summary>
/// 事前更新
/// </summary>
void ThreadShot::PreUpdate()
{
	//基本データのリセット
	m_continuationTimer = 0;
	m_distance = INITIAL_DISTANCE;

	Scene* scene = m_thread->GetScene();
	//パーティクルの取得
	std::vector<ThreadParticle*> threadParticle = m_thread->GetThreadParticles();
	//データ取得
	Thread::ThreadData data = m_thread->GetData();
	//パーティクルを生成
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		//すり抜けフラグ(最後尾のみすり抜けを防ぐ)
		bool isdetection = i == PARTICLE_NUM - 1;
		UNREFERENCED_PARAMETER(isdetection);
		//コライダー生成フラグ
		bool iscollider = i % 10 == 0 || isdetection;/*true;*/
		//糸パーツ生成
		ThreadParticle* addparticle = scene->AddObject<ThreadParticle>(scene, m_thread,iscollider, isdetection);
		threadParticle.emplace_back(addparticle);
		//正常に稼働するためにわずかにずらす
		addparticle->GetTransform()->Translate(data.m_startPosition);
		addparticle->GetTransform()->Translate(data.m_direction * (i + 1.0f) * 0.01f);
		//力を与える
		addparticle->GetRigidbody()->AddForce(data.m_direction * m_parameter->INITIAL_POWER);
	}

	//先端フラグをオン
	threadParticle.back()->SetIsTip(true);
	//少し重くする
	auto rigidbody = threadParticle.back()->GetComponent<Rigidbody>();
	rigidbody->SetMass(3.0f);

	//糸をつなげる
	RopeSolver* ropeSolver = m_thread->GetRopeSolver();
	//ホルダーと糸はじめ
	ropeSolver->Conect(data.m_holder, threadParticle.front());
	//糸同士
	for (int i = 0; i < threadParticle.size() - 1; i++)
	{
		ropeSolver->Conect(threadParticle[i], threadParticle[i + 1]);
	}

	//ホルダ-への糸の影響をなしにする
	Particle* holderParticle = data.m_holder->GetComponent<Particle>();
	holderParticle->SetIsMove(false);
	//糸の先端に力を与える
	threadParticle.back()->GetRigidbody()->AddForce(data.m_direction * m_parameter->INITIAL_POWER_TIP);
	//糸の長さを設定
	m_thread->SetRopeDistance(m_distance);

	m_thread->SetThreadParticle(threadParticle);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
void ThreadShot::Update(float deltaTime)
{
	//時間加算
	m_continuationTimer += deltaTime;
	//先のほうに力を与えて伸ばす
	ReAcceleration();
	//制約距離を伸ばす
	m_distance += deltaTime * m_parameter->EXTEND_SPEED;
	m_thread->GetRopeSolver()->SetDistance(m_distance);
	//1秒経過で消す
	if (m_continuationTimer > m_parameter->DELETE_TIME)
	{
		ChangeState(ThreadState::State::Cut);
	}
}

/// <summary>
/// 事後更新
/// </summary>
void ThreadShot::PostUpdate()
{
}

/// <summary>
/// 再加速
/// </summary>
void ThreadShot::ReAcceleration()
{
	//パーティクルの取得
	std::vector<ThreadParticle*> threadParticle = m_thread->GetThreadParticles();
	//データ取得
	Thread::ThreadData data = m_thread->GetData();
	//空なら返す
	if (threadParticle.empty())return;
	if (data.m_target != nullptr)
	{
		//ターゲットに向かって力を与える
		data.m_direction = data.m_target->GetTransform()->GetWorldPosition() - threadParticle.back()->GetTransform()->GetPosition();
		data.m_direction.Normalize();
	}
	else
	{
		DirectX::SimpleMath::Vector3 velocity = threadParticle.back()->GetRigidbody()->GetVelocity();
		velocity.Normalize();
		data.m_direction -= velocity * 0.5f;
		data.m_direction.Normalize();
	}
	//糸の先端に力を与える
	threadParticle.back()->GetRigidbody()->AddForce(data.m_direction * m_parameter->ADD_POWER);
}
