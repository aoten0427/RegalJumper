// ================================================================ 
// ファイル名 : Particle.h
// 作成者 : 景山碧天
// 説明 :  XPBDに用いるパーティクル
// ================================================================

#pragma once
#include"Base/Component/Component.h"

class Rigidbody;
class Constraint;

class Particle :public Component
{
public:
	//予測位置を返す
	DirectX::SimpleMath::Vector3 GetPredictedPosition() { return m_predictedPosition; }
	//予測位置をセット
	void SetPredictedPosition(const DirectX::SimpleMath::Vector3& position) { m_predictedPosition = position; }
	//逆重さを返す
	float GetReverseMass() const { return m_reverseMass; }
	//リジッドボディ取得
	Rigidbody* GetRigidbody() { return m_rigidbody; }
	//移動フラグセット
	bool GetIsMove() { return m_isMove; }
	//移動フラグ取得
	void SetIsMove(bool move) { m_isMove = move; }
private:
	//リジッドボディ	
	Rigidbody* m_rigidbody;
	//つながり
	std::vector<Constraint*> m_constraint;
	//予測位置
	DirectX::SimpleMath::Vector3 m_predictedPosition;
	//反転重さ
	float m_reverseMass;
	//更新確認
	bool m_isStep;
	//前フレーム座標
	DirectX::SimpleMath::Vector3 m_backPosition;
	//移動フラグ
	bool m_isMove;
public:
	Particle(Object* object);
	~Particle() override = default;
	//アップデート
	void UpdatePosition(float deltaTime);
	//計算更新
	void Step(float deltatime, Constraint* origin = nullptr);
	//更新フラグリセット
	void ReStart() { m_isStep = false; }
	//つながり追加
	void AddConstraint(Constraint* constraint);
	//つながり削除
	void DeleteConstraint(Constraint* constraint);
	//つながりの個数を返す
	int GetConstraintNum() { return (int)m_constraint.size(); }
	//データのクリア
	void Clear();
};