// ================================================================ 
// ファイル名 : Particle.cpp
// 作成者 : 景山碧天
// 説明 :  XPBDに用いるパーティクル
// ================================================================
#include"pch.h"
#include"Particle.h"
#include"Base/Base.h"
#include"Game/Play/Thread/Constraint.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object"></param>
Particle::Particle(Object* object):Component(object)
	,
	m_rigidbody{ nullptr },
	m_constraint{},
	m_predictedPosition{ DirectX::SimpleMath::Vector3::Zero },
	m_reverseMass{0},
	m_isStep{ false },
	m_backPosition{ DirectX::SimpleMath::Vector3::Zero },
	m_isMove{ true }
{
	//リジッドボディ取得
	m_rigidbody = object->GetComponent<Rigidbody>();
	assert(m_rigidbody != nullptr && "リジッドボディがありません");
	//計算に必要なデータ取得
	m_reverseMass = 1 / m_rigidbody->GetMass();
	m_backPosition = m_rigidbody->GetPosition() - m_rigidbody->GetVelocity();
}

/// <summary>
/// 位置更新
/// </summary>
/// <param name="deltaTime"></param>
void Particle::UpdatePosition(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	DirectX::SimpleMath::Vector3 pos = m_rigidbody->GetPosition();
	//移動量から速度を逆算
	DirectX::SimpleMath::Vector3 vel = pos - m_backPosition;
	//予測位置を更新
	m_predictedPosition = pos + vel;
	//位置を保存
	m_backPosition = pos;
}

/// <summary>
/// 計算更新
/// </summary>
/// <param name="deltatime"></param>
/// <param name="origin"></param>
void Particle::Step(float deltatime, Constraint* origin)
{
	//この回に実行していなければ実行
	if (m_isStep)return;
	m_isStep = true;
	for (int i = 0; i < m_constraint.size(); i++)
	{
		if (m_constraint[i] == origin)continue;
		m_constraint[i]->Compute(this, deltatime);
	}
}

/// <summary>
/// つながり追加
/// </summary>
/// <param name="constraint"></param>
void Particle::AddConstraint(Constraint* constraint)
{
	auto add = std::find(m_constraint.begin(), m_constraint.end(), constraint);
	if (add != m_constraint.end())return;
	m_constraint.push_back(constraint);
}

/// <summary>
/// つながり削除
/// </summary>
/// <param name="constraint"></param>
void Particle::DeleteConstraint(Constraint* constraint)
{
	auto del = std::find(m_constraint.begin(), m_constraint.end(), constraint);
	if (del == m_constraint.end())return;
	m_constraint.erase(del);
}

/// <summary>
/// データのクリア
/// </summary>
void Particle::Clear()
{
	m_reverseMass = 1 / m_rigidbody->GetMass();
	m_backPosition = m_rigidbody->GetPosition() - m_rigidbody->GetVelocity();
	m_constraint.clear();
}
