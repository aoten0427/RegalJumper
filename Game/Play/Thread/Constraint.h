// ================================================================ 
// ファイル名 : Constraint.h
// 作成者 : 景山碧天
// 説明 :  パーティクル同士の制約を管理
// ================================================================

#pragma once
#include <SimpleMath.h>

class Particle;

class Constraint
{
private:
	//ラグランジュ乗数
	float m_lagrange;
	//柔軟性
	float m_flexibility;

	//繋げるパーティクル
	Particle* m_particle1;
	Particle* m_particle2;
	//制約距離
	float m_distance;
	//
	float m_time;
public:
	//コンストラクタ
	Constraint(Particle* particle1, Particle* particle2);
	//デストラクタ
	~Constraint() = default;
	//パラメータのリセット
	void ResetParameter(float lagurange, float flexibillity);
	//制約による計算を実行
	void Compute(Particle* origin, float deltatime);
	//制約距離を設定
	void SetDistance(float distance) { m_distance = distance; }
	//現在の距離から制約距離を設定
	void SetDistance();
	//つながっているか判断
	bool IsConnect(Particle* particle1, Particle* particle2);
private:
	float ComputeLagrange(float deltatime);
	DirectX::SimpleMath::Vector3 ComputePosition(float lagrange);
};