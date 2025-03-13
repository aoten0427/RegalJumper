#include"pch.h"
#include"Reticle.h"
#include"Base/Base.h"
#include"Base/Camera/Camera.h"
#include"Game/Play/Player/Player.h"
#include"Base/Event/Subject.h"

constexpr float LENTH = 195;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
/// <param name="player">プレイヤー</param>
Reticle::Reticle(Scene* scene, Player* player):Object(scene)
	,
	m_player{player},
	m_caemra{scene->GetCamera()},
	m_ishit{false},
	m_oldhit{false}
{
	Rigidbody* rigidobyd = AddComponent<Rigidbody>(this);
	//判定を作成
	m_segment = AddComponent<Segment>(this, CollisionType::TRIGGER, rigidobyd, false);
	//サブジェクト作成
	m_subject = AddComponent<Subject<bool>>(this, "Reticle");
}

/// <summary>
/// 更新
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Reticle::ObjectUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	using namespace DirectX::SimpleMath;
	//プレイヤーの位置に合わせる
	GetTransform()->SetPosition(m_player->GetTransform()->GetPosition());
	//判定の向きをカメラの向いている方向に合わせる
	Vector3 dire = m_caemra->GetTargetPosition() - m_caemra->GetEyePosition();
	dire.Normalize();
	m_segment->SetEndPos(dire * LENTH);

	//前フレームから当たった状態が変わった場合通知
	if (m_oldhit != m_ishit)
	{
		m_subject->Notify(m_ishit);
	}
	//リセット
	m_oldhit = m_ishit;
	m_ishit = false;

}

/// <summary>
/// Triggerの実行有無 ステージと当たったか調べる
/// </summary>
/// <param name="collider"></param>
/// <returns></returns>
bool Reticle::IsTriggerAct(Collider* collider)
{
	if (collider->GetObject()->GetTag() == ObjectTag::Stage)return true;
	return false;
}

/// <summary>
/// Trigger処理
/// </summary>
/// <param name="collider"></param>
void Reticle::OnTrigger(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
	m_ishit = true;
}
