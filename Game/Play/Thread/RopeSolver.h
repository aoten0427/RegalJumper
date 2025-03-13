// ================================================================ 
// ファイル名 : RopeSolver.h
// 作成者 : 景山碧天
// 説明 :  一つの糸の計算を管理
// ================================================================

#pragma once
#include"Base/Component/Component.h"

class Constraint;
class Particle;
class Rigidbody;

class RopeSolver :public Component
{
private:
	//パーティクル
	std::vector<Particle*> m_particles;
	//パーティクル間の制約
	std::vector<std::unique_ptr<Constraint>> m_constraints;

	float m_flexibility;
public:
	//コンストラクタ
	RopeSolver(Object* object);
	//デストラクタ
	~RopeSolver()override = default;
	//アップデート
	void Update(float deltaTime);
	//繋げる
	void Conect(Object* object1, Object* object2);
	//制約距離設定
	void SetDistance(float distance);
	//制約距離設定
	void SetDistance();

	void SetFlexibility(float flexibility) { m_flexibility = flexibility; }
	//つながりの削除
	void DeleteConstraint(Constraint* constraint);
	//パーティクルの削除
	void DeleteParticle(Particle* particle);
	//パーティクル取得
	const std::vector<Particle*> GetParticles() { return m_particles; }
	//データクリア
	void Clear();
};