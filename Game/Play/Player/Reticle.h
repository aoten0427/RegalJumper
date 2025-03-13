// ================================================================ 
// ファイル名 : Reticle.h
// 作成者 : 景山碧天
// 説明 :  プレイヤーのレティクル
// ================================================================
#pragma once
#include"Base/Object/Object.h"

class Player;
class Camera;
class Segment;
template<typename ...Args>
class Subject;

class Reticle :public Object
{
private:
	//プレイヤー
	Player* m_player;
	//カメラ
	Camera* m_caemra;
	//判定
	Segment* m_segment;
	//ヒット時のサブジェクト
	Subject<bool>* m_subject;
	//あたったかどうか
	bool m_ishit;
	//前フレームの当たり
	bool m_oldhit;
public:
	//コンストラクタ
	Reticle(Scene* scene,Player* player);
	//デストラクタ
	~Reticle() override = default;
	//更新
	void ObjectUpdate(float deltatime)override;
	//Triggerの実行有無
	bool IsTriggerAct(Collider* collider) override;
	//Trigger処理
	void OnTrigger(Collider* collider) override;
};