// ================================================================ 
// ファイル名 : Constraint.cpp
// 作成者 : 景山碧天
// 説明 :  パーティクル同士の制約を管理
// ================================================================
#include"pch.h"
#include"Constraint.h"
#include"Game/Play/Thread/Particle.h"
#include"Base/MyLibraries/Functions.h"
#include"Base/Tween/Easing.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="particle1">パーティクル1</param>
/// <param name="particle2">パーティクル2</param>
Constraint::Constraint(Particle* particle1, Particle* particle2)
	:
	m_lagrange{ 0 },
	m_flexibility{ 0 },
	m_particle1{ particle1 },
	m_particle2{ particle2 },
	m_distance{ 1.5f },
	m_time{0}
{
	//パーティクルに自信を登録
	particle1->AddConstraint(this);
	particle2->AddConstraint(this);
}

/// <summary>
/// パラメータのリセット
/// </summary>
/// <param name="lagurange"></param>
/// <param name="flexibillity"></param>
void Constraint::ResetParameter(float lagurange, float flexibillity)
{
	m_lagrange = lagurange;
	m_flexibility = flexibillity;
}

/// <summary>
/// 制約による計算を実行
/// </summary>
/// <param name="origin"></param>
/// <param name="deltatime"></param>
void Constraint::Compute(Particle* origin, float deltatime)
{
	m_time += deltatime;

	float lagrange = ComputeLagrange(deltatime);
	DirectX::SimpleMath::Vector3 distance = ComputePosition(lagrange);

	m_lagrange += lagrange;

	//パーティクルの予測位置を更新
	m_particle1->SetPredictedPosition(m_particle1->GetPredictedPosition() + m_particle1->GetReverseMass() * distance);
	m_particle2->SetPredictedPosition(m_particle2->GetPredictedPosition() - m_particle2->GetReverseMass() * distance);

	//次のパーティクルの計算を実行
	Particle* next = m_particle1 == origin ? m_particle2 : m_particle1;
	next->Step(deltatime, this);
}

/// <summary>
/// 制約距離を設定
/// </summary>
void Constraint::SetDistance()
{
	using namespace DirectX::SimpleMath;
	//現在の距離を制約距離とする
	Vector3 vector = m_particle2->GetPredictedPosition() - m_particle1->GetPredictedPosition();
	float distance = vector.Length();
	m_distance = distance;
}

/// <summary>
/// つながっているか判断
/// </summary>
/// <param name="particle1"></param>
/// <param name="particle2"></param>
/// <returns></returns>
bool Constraint::IsConnect(Particle* particle1, Particle* particle2)
{
	if (particle1 == particle2)return false;
	if (m_particle1 != particle1 && m_particle2 != particle2)return false;
	if (m_particle2 != particle1 && m_particle2 != particle2)return false;

	return true;
}


float Constraint::ComputeLagrange(float deltatime)
{
	using namespace DirectX::SimpleMath;

	// 予測位置の差分ベクトルを計算
	Vector3 vector = m_particle2->GetPredictedPosition() - m_particle1->GetPredictedPosition();
	// 現在の距離を計算
	float distance = vector.Length();
	// 制約条件 C = 現在の距離 - 設定された制約距離
	float C = distance - m_distance;
	// 拘束の柔軟性を考慮した補正係数を計算
	float αTilda = m_flexibility / (deltatime * deltatime);
	// 方向ベクトルを正規化 (制約の勾配)
	Vector3 ΔC = vector / distance;
	// 逆質量の合計を取得
	float invM = m_particle1->GetReverseMass() + m_particle2->GetReverseMass();
	// 修正されたラグランジュ乗数を計算
	return (C - αTilda * m_lagrange) / (ΔC.Dot(invM * ΔC) + αTilda);
}

DirectX::SimpleMath::Vector3 Constraint::ComputePosition(float lagrange)
{
	// 予測位置の差分ベクトルを取得
	auto ΔC = (m_particle2->GetPredictedPosition() - m_particle1->GetPredictedPosition());
	// 正規化して方向ベクトルを求める
	ΔC.Normalize();

	// ラグランジュ乗数に基づく位置修正量を計算
	return ΔC * lagrange;
}
