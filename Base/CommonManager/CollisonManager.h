// ================================================================ 
// ファイル名 : CollisionManager.h
// 作成者 : 景山碧天
// 説明 :  衝突判定を管理
// ================================================================

#pragma once
#include"Base/Component/Collider/Collider.h"

class Rigidbody;

class CollisionManager
{
private:
	//衝突判定オブジェクト情報
	struct  CollisionData
	{
		Object* m_holder;     //保持者
		Collider* m_collider;   //衝突判定
		Rigidbody* m_rigidbody;  //保持リジッドボディ
		CollisionType m_type;       //判定タイプ
	};
private:
	////管理衝突データ
	std::vector<CollisionData> m_collisionDates;
	//すり抜けを防止するリジッドボディ
	/*std::unordered_set<Rigidbody*> m_detectionObject;*/
public:
	//コンストラクタ
	CollisionManager();
	//デストラクタ
	~CollisionManager() = default;
	//アップデート
	void Update();

	//コライダー追加
	void AddCollider(Collider* collider, CollisionType type);
	//コライダー削除
	void ReMoveCollider(Collider* collider);
	//線分用判定
	void RayCollision(Segment* segment, CollisionType type, DirectX::SimpleMath::Vector3* pushback);
private:
	//衝突判定を実行するか判定
	bool IsAct(int collision1num, int collision2num);
	//移動オブジェクト同士
	void Collision(int i, int j);
	//固定オブジェクトと移動オブジェクト
	void Fixed_Collision(int i, int j);
	//接触確認
	void Trigger(int i, int j);
	
};