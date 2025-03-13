// ================================================================ 
// ファイル名 : CollisionManager.cpp
// 作成者 : 景山碧天
// 説明 :  衝突判定を管理
// ================================================================

#include"pch.h"
#include"CollisonManager.h"
#include"Base/Component/Collider/Collision.h"
#include"Base/Object/Object.h"
#include"Base/Component/Rigidbody/Rigidbody.h"

/// <summary>
/// コンストラクタ
/// </summary>
CollisionManager::CollisionManager()
{
}


/// <summary>
/// アップデート　衝突判定を実行
/// </summary>
void CollisionManager::Update()
{
	for (int i = 0; i < m_collisionDates.size(); i++)
	{
		for (int j = i + 1; j < m_collisionDates.size(); j++)
		{
			//衝突判定を実行するか判断
			if (!IsAct(i, j))continue;

			//固定オブジェクトと移動オブジェクト
			if (m_collisionDates[i].m_type == CollisionType::FIXED && m_collisionDates[j].m_type == CollisionType::COLLISION)
			{
				Fixed_Collision(i, j);
			}
			if (m_collisionDates[i].m_type == CollisionType::FIXED && m_collisionDates[j].m_type == CollisionType::TRIGGER)
			{
				Trigger(i, j);
			}
			//移動オブジェクトと移動オブジェクト
			else if(m_collisionDates[i].m_type == CollisionType::COLLISION && m_collisionDates[j].m_type == CollisionType::COLLISION)
			{
				Collision(i, j);
			}
			//移動オブジェクトとすり抜けオブジェクト
			else if (m_collisionDates[i].m_type == CollisionType::COLLISION && m_collisionDates[j].m_type == CollisionType::TRIGGER)
			{
				Trigger(i, j);
			}
			//すり抜けオブジェクトとすり抜けオブジェクト
			else if (m_collisionDates[i].m_type == CollisionType::TRIGGER && m_collisionDates[j].m_type == CollisionType::TRIGGER)
			{
				Trigger(i, j);
			}
		}
	}
}

/// <summary>
/// コライダー追加
/// </summary>
/// <param name="collider"></param>
/// <param name="type"></param>
void CollisionManager::AddCollider(Collider* collider, CollisionType type)
{
	//軌跡起動用はパス
	if (type == CollisionType::ORBIT)return;

	//新しいコライダーデータを作り中身を設定
	CollisionData newdata{
		collider->GetObject(),
		collider,
		collider->GetRigidbody(),
		type
	};

	m_collisionDates.push_back(newdata);

	//判定のタイプごとに並び替え
	std::sort(m_collisionDates.begin(), m_collisionDates.end(), [](CollisionData& data1, CollisionData& data2) {
		return (int)data1.m_type < (int)data2.m_type;
		});
}

/// <summary>
/// コライダー削除
/// </summary>
/// <param name="collider"></param>
void CollisionManager::ReMoveCollider(Collider* collider)
{

	auto itr = std::find_if(m_collisionDates.begin(), m_collisionDates.end(), [&, collider]
	(const CollisionData& collisiondata) {
			return collisiondata.m_collider == collider;
		});

	if (itr != m_collisionDates.end())
	{
		m_collisionDates.erase(itr);
	}
}


/// <summary>
/// 衝突判定を実行するか判定
/// </summary>
/// <param name="collision1num">判定1</param>
/// <param name="collision2num">判定2</param>
/// <returns>実行有無</returns>
bool CollisionManager::IsAct(int collision1num, int collision2num)
{
	//サイズ外をパス
	if (collision2num >= m_collisionDates.size())return false;
	//非アクティブ状態ならパス
	if (!m_collisionDates[collision1num].m_collider->GetActive())return false;
	if (!m_collisionDates[collision2num].m_collider->GetActive())return false;
	//同オブジェクトならパス
	if (m_collisionDates[collision1num].m_holder == m_collisionDates[collision2num].m_holder)return false;
	//それぞれリジッドボディがなければパス
	if (m_collisionDates[collision1num].m_rigidbody == nullptr && m_collisionDates[collision2num].m_rigidbody == nullptr)return false;
	//両方固定オブジェクトならパス
	if (m_collisionDates[collision1num].m_type == CollisionType::FIXED && m_collisionDates[collision2num].m_type == CollisionType::FIXED)return false;

	return true;
}

/// <summary>
/// Collision同士
/// </summary>
/// <param name="i">判定1</param>
/// <param name="j">判定2</param>
void CollisionManager::Collision(int i, int j)
{
	using namespace DirectX::SimpleMath;

	//判定をとらないならパス
	if (!m_collisionDates[i].m_holder->IsCollisionAct(m_collisionDates[j].m_collider))return;
	if (!m_collisionDates[j].m_holder->IsCollisionAct(m_collisionDates[i].m_collider))return;

	//めり込み量を計算
	Vector3 pushback = Collision::OnCollision(*m_collisionDates[i].m_collider, *m_collisionDates[j].m_collider);
	//めり込みがないならパス
	if (pushback.Length() == 0)return;

	//双方の重さを考慮して移動量を計算
	float addmass = m_collisionDates[i].m_rigidbody->GetMass() + m_collisionDates[j].m_rigidbody->GetMass();
	m_collisionDates[i].m_holder->PushBack(pushback * (1 - (m_collisionDates[i].m_rigidbody->GetMass() / addmass)));
	m_collisionDates[j].m_holder->PushBack(-pushback * (1 - (m_collisionDates[j].m_rigidbody->GetMass() / addmass)));
}

/// <summary>
/// FixedとCollision
/// </summary>
/// <param name="i">判定1</param>
/// <param name="j">判定2</param>
void CollisionManager::Fixed_Collision(int i, int j)
{
	using namespace DirectX::SimpleMath;

	//判定をとらないならパス
	if (!m_collisionDates[i].m_holder->IsCollisionAct(m_collisionDates[j].m_collider))return;
	if (!m_collisionDates[j].m_holder->IsCollisionAct(m_collisionDates[i].m_collider))return;

	//めり込み量を計算
	Vector3 pushback = Collision::OnCollision(*m_collisionDates[i].m_collider, *m_collisionDates[j].m_collider);
	//めり込みがないならパス
	if (pushback.Length() == 0)return;

	m_collisionDates[j].m_holder->PushBack(-pushback);
	m_collisionDates[i].m_holder->OnCollision(m_collisionDates[j].m_collider);
	m_collisionDates[j].m_holder->OnCollision(m_collisionDates[i].m_collider);
}

/// <summary>
/// Trigger
/// </summary>
/// <param name="i">判定1</param>
/// <param name="j">判定2</param>
void CollisionManager::Trigger(int i, int j)
{
	using namespace DirectX::SimpleMath;

	//判定をとらないならパス
	if (!m_collisionDates[i].m_holder->IsTriggerAct(m_collisionDates[j].m_collider))return;
	if (!m_collisionDates[j].m_holder->IsTriggerAct(m_collisionDates[i].m_collider))return;

	//衝突有無を判定
	bool hit = Collision::OnTrigger(*m_collisionDates[i].m_collider, *m_collisionDates[j].m_collider);

	if (!hit)return;
	m_collisionDates[i].m_holder->OnTrigger(m_collisionDates[j].m_collider);
	m_collisionDates[j].m_holder->OnTrigger(m_collisionDates[i].m_collider);
}

/// <summary>
/// ステージと線分との当たり判定を取る
/// </summary>
/// <param name="segment">線分</param>
/// <param name="type">判定タイプ</param>
/// <param name="pushback">戻し量</param>
void CollisionManager::RayCollision(Segment* segment, CollisionType type, DirectX::SimpleMath::Vector3* pushback)
{
	using namespace DirectX::SimpleMath;

	for (int i = 0; i < m_collisionDates.size(); i++)
	{
		if (m_collisionDates[i].m_type != CollisionType::FIXED)continue;
		if (m_collisionDates[i].m_holder->GetTag() != ObjectTag::Stage)continue;

		if (type == CollisionType::COLLISION)
		{
			//めり込み量を計算
			Vector3 push = Collision::OnCollision(*m_collisionDates[i].m_collider, *segment);
			//めり込みがないならパス
			if (push.Length() == 0)continue;
			*pushback = push;
		}
	}
}


