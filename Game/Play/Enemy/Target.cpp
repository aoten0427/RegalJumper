// ================================================================ 
// ファイル名 : Target.cpp
// 作成者 : 景山碧天
// 説明 :  ターゲット
// ================================================================
#include"pch.h"
#include"Target.h"
#include"Base/Component/Transform/Transform.h"
#include"Base/Component/Collider/Collider.h"
#include"Base/Event/Subject.h"
#include"Base/Event/Observer.h"


int Target::TARGET_ID = 0;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
/// <param name="holder">所属オブジェクト</param>
/// <param name="type">ターゲットタイプ</param>
Target::Target(Scene* scene, Object* holder, TargetType type):Object(scene)
	,
	m_id{TARGET_ID},
	m_type{ type },
	m_holder{ holder },
	m_isActive{ false },
	m_isTarget{ false }
{
	//ID加算
	TARGET_ID++;
	//親子設定
	GetTransform()->SetParent(holder->GetTransform());
	//コライダー生成
	m_collider = AddComponent<Sphere>(this, CollisionType::TRIGGER, nullptr,false,3.0f);
	//破壊サブジェクト生成
	std::string subjectName = "Target" + std::to_string(m_id);
	m_destroySubject = AddComponent<Subject<>>(this, subjectName);
}

/// <summary>
/// デストラクタ
/// </summary>
Target::~Target()
{
	//サーチャーに自身を消すよう指示
	m_destroySubject->Notify();
}

/// <summary>
/// 範囲内判定
/// </summary>
/// <param name="pos">サーチャーの位置</param>
/// <param name="dire">サーチャーの向き</param>
/// <param name="range">検索半径</param>
/// <param name="vision">検索角度</param>
/// <returns>範囲に入っているか</returns>
bool Target::IsRange(const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& dire, const float& range, const float& vision)
{
	//サーチャーとの距離を計算
	DirectX::SimpleMath::Vector3 PosToTarget = m_collider->GetTransform().GetWorldPosition() - pos;
	//サーチャー探索範囲外ならアクティブをオフに
	if (PosToTarget.Length() > range)
	{
		m_isActive = false;
		return false;
	}
	PosToTarget.Normalize();
	//範囲角度内かを判断
	if (dire.Dot(PosToTarget) > vision)
	{
		m_isActive = true;
		return true;
	}
	return false;
}

/// <summary>
/// Trigger実行判定 サーチャーのみ判定を扱う
/// </summary>
/// <param name="collider">コライダー</param>
/// <returns>判定有無</returns>
bool Target::IsTriggerAct(Collider* collider)
{
	if (collider->GetObject()->GetTag() == ObjectTag::Search)return true;
	return false;
}

/// <summary>
/// サーチャーの登録
/// </summary>
/// <param name="observer"></param>
void Target::SetSearch(Observer<>* observer)
{
	std::string subjectName = "Target" + std::to_string(m_id);
	observer->RegistrationSubject(subjectName);
}

/// <summary>
/// サーチャーの解除
/// </summary>
/// <param name="observer"></param>
void Target::RemoveSearch(Observer<>* observer)
{
	std::string subjectName = "Target" + std::to_string(m_id);
	observer->RemoveSubject(subjectName);
}
