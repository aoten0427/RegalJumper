// ================================================================ 
// ファイル名 : Search.cpp
// 作成者 : 景山碧天
// 説明 :  ターゲットを探すサーチャー
// ================================================================
#include"pch.h"
#include"Search.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Component/Collider/Collider.h"
#include"Base/Component/Rigidbody/Rigidbody.h"
#include"Base/Event/Observer.h"

#include"Base/Scene/Scene.h"
#include"Base/Camera/Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
/// <param name="holder">所属オブジェクト</param>
/// <param name="radius">半径</param>
Search::Search(Scene* scene,Object* holder, float radius):Object(scene)
	,
	m_target{ nullptr },
	m_searchType{ {Target::TargetType::Attack,false},
		{Target::TargetType::Move,false},
		{Target::TargetType::Player,false }
	},
	m_viewingDirection{ DirectX::SimpleMath::Vector3::Zero },
	m_range{ radius },
	m_vision{ 0.95f }
{
	//親子設定
	GetTransform()->SetParent(holder->GetTransform());
	//判定作成(判定をとるためのリジッドボディも作成)
	Rigidbody* rigidbody = AddComponent<Rigidbody>(this);
	AddComponent<Sphere>(this, CollisionType::TRIGGER,rigidbody,false, m_range);
	//オブザーバー作成
	m_targetDelete = AddComponent<Observer<>>(this);
	m_targetDelete->SetFunction([&]() {m_target = nullptr; });
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Search::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	if (m_target != nullptr)
	{
		//範囲内検索
		if (!m_target->IsRange(GetScene()->GetCamera()->GetEyePosition(),
			m_viewingDirection, m_range, m_vision))
		{
			//登録解除
			m_target->SetIsTarget(false);
			m_target->RemoveSearch(m_targetDelete);
			m_target = nullptr;
		}
	}
}

/// <summary>
/// Trigger実行有無 ターゲットのみ判定
/// </summary>
/// <param name="collider">判定</param>
/// <returns>判定有無</returns>
bool Search::IsTriggerAct(Collider* collider)
{
	//ターゲット以外はパス
	if (collider->GetObject()->GetTag() == ObjectTag::Target)return true;
	return false;
}

/// <summary>
/// Trigger処理
/// </summary>
/// <param name="collider">判定</param>
void Search::OnTrigger(Collider* collider)
{
	using namespace DirectX::SimpleMath;
	if (collider->GetObject()->GetTag() == ObjectTag::Target)
	{
		//ターゲットに変換
		Target* target = dynamic_cast<Target*>(collider->GetObject());
		//範囲外なら返す
		if (!target->IsRange(GetScene()->GetCamera()->GetEyePosition(),
			m_viewingDirection, m_range, m_vision))return;
		
		//現在のと同一ならパス
		if (m_target == target)return;
		
		//ターゲットに設定
		if (m_target == nullptr)
		{
			m_target = target;
			m_target->SetIsTarget(true);
			m_target->SetSearch(m_targetDelete);
		}
		else//現在ターゲットがある場合
		{
			SelectTarget(target);
		}
		
	}
}

/// <summary>
/// ターゲットを選択
/// </summary>
/// <param name="newTarget">新しいターゲット</param>
void Search::SelectTarget(Target* newTarget)
{
	using namespace DirectX::SimpleMath;
	//二つのターゲットの距離を見て近いほうを選択する
	float dire1 = Vector3::Distance(GetTransform()->GetPosition(), m_target->GetTransform()->GetWorldPosition());
	float dire2 = Vector3::Distance(GetTransform()->GetPosition(), newTarget->GetTransform()->GetWorldPosition());
	if (dire1 > dire2)
	{
		//登録解除
		m_target->SetIsTarget(false);
		m_target->RemoveSearch(m_targetDelete);
		//登録
		m_target = newTarget;
		m_target->SetIsTarget(true);
		m_target->SetSearch(m_targetDelete);
	}
}


