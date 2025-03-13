// ================================================================ 
// ファイル名 : Rigidbody.h
// 作成者 : 景山碧天
// 説明 :  オブジェクトの移動を管理する
// ================================================================

#pragma once
#include"Base/Component/Component.h"

class Rigidbody :public Component
{
public:
	//体重取得
	float GetMass() const { return m_mass; }
	//体重設定
	void SetMass(float mass) { m_mass = mass; }
	//速度取得
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	//速度設定
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	//追加速度取得
	DirectX::SimpleMath::Vector3 GetAddforce() const { return m_addforce; }
	//追加速度設定
	void SetAddForce(const DirectX::SimpleMath::Vector3& addforce) { m_addforce = addforce; }
	//追加速度増加
	void AddForce(const DirectX::SimpleMath::Vector3& addforce) { m_addforce += addforce; }
	//固定フラグ取得
	bool GetFixed() const { return m_isFixed; }
	//固定フラグ設定
	void SetFixed(float fixed) { m_isFixed = fixed; }
	//軽減率セット
	void SetReduction(float reduction) { m_reduction = reduction; }
	//すり抜けフラグ取得
	bool GetIsDetection() const { return m_isDetection; }
private:
	//体重
	float m_mass;
	//速度
	DirectX::SimpleMath::Vector3 m_velocity;
	//追加速度
	DirectX::SimpleMath::Vector3 m_addforce;
	//固定フラグ
	bool m_isFixed;
	//スピード軽減率
	float m_reduction;
	//すり抜け防止
	bool m_isDetection;
public:
	//コンストラクタ
	Rigidbody(Object* object);
	//デストラクタ
	~Rigidbody();
	//スピードの計算
	void Compute(float deltatime);
	//ポジションを返す
	DirectX::SimpleMath::Vector3 GetPosition();
};