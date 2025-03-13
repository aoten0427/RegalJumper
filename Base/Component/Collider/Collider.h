// ================================================================ 
// ファイル名 : Collider.h
// 作成者 : 景山碧天
// 説明 :  各当たり判定
// ================================================================
#pragma once
#include"Base/Component/Collider/Collider.h"
#include"Base/Component/Transform/Transform.h"

class Rigidbody;

//判定時のタイプ
enum class CollisionType
{
	FIXED,
	COLLISION,
	TRIGGER,
	ORBIT
};

class Collider:public Component
{
public:
	//コライダータイプ
	enum ColliderTag
	{
		AABB = 1 << 0,
		OBB = 1 << 2,
		SPHERE = 1 << 3,
		SEGMENT = 1 << 4,
		TRIANGLE = 1 << 5,
		QUAD = 1 << 6
	};
public:
	//タグ取得
	const ColliderTag& GetColliderTag() const { return m_colliderTag; }
	//計算用トランスフォーム
	Transform GetTransform()const { return *m_transform; }
	//リジットボディ取得
	Rigidbody* GetRigidbody() { return m_rigidbody; }
	//ポジション取得
	DirectX::SimpleMath::Vector3 GetPosition() const{ return m_position; }
	//スケール取得
	DirectX::SimpleMath::Vector3 GetScale()const { return m_scale; }
	//matrix取得
	DirectX::SimpleMath::Matrix GetMatrix()const { return m_matrix; }
	//
	bool GetIsNotPas()const { return m_isNotPas; };
	void SetIsNotPas(const bool& isnotpas) { m_isNotPas = isnotpas; }
private:
	//タグ
	ColliderTag m_colliderTag;
	//トランスフォーム
	Transform* m_transform;
	//リジッドボディ
	Rigidbody* m_rigidbody;
	//位置
	DirectX::SimpleMath::Vector3 m_position;
	//大きさ
	DirectX::SimpleMath::Vector3 m_scale;
	//自身のmatrix
	DirectX::SimpleMath::Matrix m_matrix;
	//すり抜け判定フラグ(すり抜けを防止する側のフラグ)
	bool m_isNotPas;
public:
	Collider(Object* object, ColliderTag tag, CollisionType type, Rigidbody* rigidbody = nullptr,bool view = false);
	virtual ~Collider();

	//ポジションセット
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	//スケールセット
	void SetScale(const DirectX::SimpleMath::Vector3& scale);
	//ワールド座標取得
	DirectX::SimpleMath::Vector3 GetWorldPosition();
	//ワールドスケール取得
	DirectX::SimpleMath::Vector3 GetWorldScale();
	//ワールドmatrix取得
	virtual DirectX::SimpleMath::Matrix GetWorldMatrix();
	//バウンディングスフィア用半径取得
	virtual float GetRadius();
};

/// <summary>
/// AABB
/// </summary>
class AABB final: public Collider
{
private:
	
public:
	AABB(Object* object, CollisionType type, Rigidbody* rigidbody = nullptr, bool view = false);
	~AABB()override = default;

	DirectX::SimpleMath::Matrix GetWorldMatrix()override;

	//大きさを返す
	DirectX::SimpleMath::Vector3 GetExtents();

	float GetRadius()override;
};

/// <summary>
/// OBB
/// </summary>
class OBB final :public Collider
{
private:
public:
	OBB(Object* object, CollisionType type, Rigidbody* rigidbody = nullptr, bool view = false);
	~OBB()override = default;

	//大きさを返す
	DirectX::SimpleMath::Vector3 GetExtents();

	float GetRadius()override;
};

/// <summary>
/// 球
/// </summary>
class Sphere final :public Collider
{
private:
	float m_radius;
public:
	Sphere(Object* object, CollisionType type, Rigidbody* rigidbody = nullptr, bool view = false,float radius = 1);
	~Sphere()override = default;
	void  SetRadius(float radius);
	float GetRadius() override;
};

/// <summary>
/// 線分
/// </summary>
class Segment final :public Collider
{
private:
	//始点
	DirectX::SimpleMath::Vector3 m_strPos;
	//終点
	DirectX::SimpleMath::Vector3 m_endPos;
public:
	Segment(Object* object, CollisionType type, Rigidbody* rigidbody = nullptr, bool view = false,
		DirectX::SimpleMath::Vector3 start = DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3 end = DirectX::SimpleMath::Vector3::Zero);
	~Segment()override = default;

	//ローカル始点取得
	DirectX::SimpleMath::Vector3 GetLocalStartPos();
	//ローカル終点取得
	DirectX::SimpleMath::Vector3 GetLocalEndPos();
	//ワールド始点取得
	DirectX::SimpleMath::Vector3 GetWorldStartPos();
	//ワールド終点取得
	DirectX::SimpleMath::Vector3 GetWorldEndPos();
	//始点設定
	void SetStartPos(const DirectX::SimpleMath::Vector3& strpos) { m_strPos = strpos; }
	//終点設定
	void SetEndPos(const DirectX::SimpleMath::Vector3& endpos) { m_endPos = endpos; }
	//ベクトル取得
	DirectX::SimpleMath::Vector3 GetVector();
	//向き取得
	DirectX::SimpleMath::Vector3 GetDirection();
	//長さ取得
	float GetLength();
	//半径取得
	float GetRadius() override;
};