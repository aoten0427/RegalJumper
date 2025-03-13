// ================================================================ 
// ファイル名 :Player.h 
// 作成者 : 景山碧天
// 説明 :  プレイヤー
// ================================================================

#pragma once
#include"Base/Object/Object.h"


class Rigidbody;
class OBB;
class PlayerStateMachine;
class PlayerCenter;
class SpiderModels;
class PlayCamera;
template<typename...Args>
class Subject;
template<typename...Args>
class Observer;

class Player :public Object
{
public:
	//タグ取得
	ObjectTag GetTag() { return ObjectTag::Player; };
	//プレイヤーセンター取得
	PlayerCenter* GetPlayerCenter() const { return m_playerCenter; }
	//モデル取得
	SpiderModels* GetModel() const { return m_model; }
	//地上有無取得
	bool GetIsGround() const { return m_isGround; }
private:
	PlayerCenter* m_playerCenter;
	OBB* m_collider;
	Rigidbody* m_rigidbody;
	//モデル
	SpiderModels* m_model;
	//ステートマシン
	std::unique_ptr<PlayerStateMachine> m_stateMachine;
	//地上判定
	bool m_isGround;
	//カメラ
	PlayCamera* m_camera;
	//死亡時サブジェクト
	Subject<>* m_deathSubject;
	//リセットオブザーバー
	Observer<>* m_resetObserver;
public:
	//コンストラクタ
	Player(Scene* scene,PlayerCenter* center);
	//デストラクタ
	~Player()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
	//出現処理
	void Entery();

	//判定系
	//Triggerの実行有無
	bool IsTriggerAct(Collider* collider) override;
	//Collisionの実行有無
	bool IsCollisionAct(Collider* collider) override;
	//押し戻し(押し出し量)
	void PushBack(DirectX::SimpleMath::Vector3 pushback)override;
	//Trigger処理
	void OnTrigger(Collider* collider) override;
	//Collision処理
	void OnCollision(Collider* collider) override;
	//めり込み計算実行の有無
	bool IsDetectionAct(Collider* collider)override;

	//データリセット
	void Reset();

private:
	//ゴール判定
	void IsGoal();
	//死亡判定
	void IsDeath();
};