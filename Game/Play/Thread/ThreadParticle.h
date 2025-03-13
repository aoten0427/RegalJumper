// ================================================================ 
// ファイル名 : ThreadParticle.h
// 作成者 : 景山碧天
// 説明 :  糸の最小単位
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class Thread;
class Rigidbody;

class ThreadParticle :public Object
{
public:
	//先端設定
	void SetIsTip(bool tip) { m_isTip = tip; }
	//リジッドボディ取得
	Rigidbody* GetRigidbody() { return m_rigidbody; }
private:
	//糸全体
	Thread* m_thread;
	//リジッドボディ
	Rigidbody* m_rigidbody;
	//先端判定
	bool m_isTip;
public:
	//コンストラクタ
	ThreadParticle(Scene* scene, Thread* thread, bool iscollider, bool isdetection);
	//デストラクタ
	~ThreadParticle()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
	//Collision実行有無
	bool IsCollisionAct(Collider* collider) override;
	//Collision処理
	void OnCollision(Collider* collider)override;

	bool IsDetectionAct(Collider* collider) override;
};


