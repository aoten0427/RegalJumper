// ================================================================ 
// ファイル名 : Target.h
// 作成者 : 景山碧天
// 説明 :  ターゲット
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class Sphere;
class Search;
template<typename...Args>
class Subject;
template<typename...Args>
class Observer;

class Target :public Object
{
private:
	//識別ID
	static int TARGET_ID;
public:
	//ターゲットのタイプ
	enum class TargetType
	{
		Move,
		Attack,
		Player
	};
public:
	//タグ取得
	ObjectTag GetTag() { return ObjectTag::Target; };
	//タイプ取得
	TargetType GetType()const { return m_type; }
	//アクティブ設定
	void SetTargetActive(bool active) { m_isActive = active; }
	bool GetTargetActive()const { return m_isActive; }
	//ターゲット設定
	void SetIsTarget(const bool& Target) { m_isTarget = Target; }
	bool GetIsTarget()const { return m_isTarget; }
private:
	//自身のID
	int m_id;
	//ターゲットタイプ
	TargetType m_type;
	//ホルダー
	Object* m_holder;
	//判定
	Sphere* m_collider;
	//アクティブ(範囲内に入っているか)
	bool m_isActive;
	//ターゲット(ターゲットになっているか)
	bool m_isTarget;
	//破壊時に呼び出すサブジェクト
	Subject<>* m_destroySubject;
public:
	//コンストラクト
	Target(Scene* scene, Object* holder, TargetType type);
	//デストラクタ
	~Target()override;
	//範囲に入っているか
	bool IsRange(const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& dire,
		const float& range,
		const float& vision);
	//サーチャーの登録、解除
	void SetSearch(Observer<>* observer);
	void RemoveSearch(Observer<>* observer);
	//Triggerの実行有無
	bool IsTriggerAct(Collider* collider) override;
};
