// ================================================================ 
// ファイル名 : Search.h
// 作成者 : 景山碧天
// 説明 :  ターゲットを探すサーチャー
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Game/Play/Enemy/Target.h"

template<typename...Args>
class Observer;

class Search :public Object
{
public:
	//タグ取得
	ObjectTag GetTag() { return ObjectTag::Search; }
	//向き設定
	void SetViewingDirection(const DirectX::SimpleMath::Vector3& view) { m_viewingDirection = view; m_viewingDirection.Normalize(); }
	//捜索範囲
	void SetRange(const float& range) { m_range = range; }
	//視覚範囲設定
	void SetVision(const float& vision) { m_vision = vision; }
	//ターゲットの取得
	Target* GetTarget() { return m_target; }
private:
	//ターゲット
	Target* m_target;
	//探すターゲットの種類
	std::unordered_map<Target::TargetType, bool> m_searchType;
	//向いている方向
	DirectX::SimpleMath::Vector3 m_viewingDirection;
	//捜索範囲
	float m_range;
	//視覚範囲
	float m_vision;
	//ターゲット消去オブザーバー
	Observer<>* m_targetDelete;
public:
	//コンストラクタ
	Search(Scene* scene,Object* holder, float radius = 100.0f);
	//デストラクタ
	~Search()override = default;
	void ObjectUpdate(float deltatime)override;
	//Triggerの実行有無
	bool IsTriggerAct(Collider* collider) override;
	//Trigger処理
	void OnTrigger(Collider* collider) override;
private:
	//ターゲットを選択
	void SelectTarget(Target* newTarget);
};