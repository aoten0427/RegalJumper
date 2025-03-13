// ================================================================ 
// ファイル名 : Rigidbody.cpp
// 作成者 : 景山碧天
// 説明 :  オブジェクトの移動を管理する
// ================================================================

#include"pch.h"
#include"Rigidbody.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonManager/RIgidbodyManager.h"
#include"Base/Object/Object.h"
#include"Base/Component/Transform/Transform.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
Rigidbody::Rigidbody(Object* object):Component(object)
	,
	m_mass{ 1.0f },
	m_velocity{},
	m_addforce{},
	m_isFixed{ false },
	m_reduction{ 1.0f },
	m_isDetection{ false }
{
	//マネージャーへ登録
	auto rigidbodyManager = object->GetScene()->GetRigidbodyManager();
	rigidbodyManager->AddRigidbody(this);
}

/// <summary>
/// デストラクタ
/// </summary>
Rigidbody::~Rigidbody()
{
	//マネージャーから削除
	auto rigidbodyManager = GetObject()->GetScene()->GetRigidbodyManager();
	rigidbodyManager->RemoveRigidbody(this);
}

/// <summary>
/// スピードの計算
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Rigidbody::Compute(float deltatime)
{
	//固定中ならパス
	if (m_isFixed)return;
	using namespace DirectX::SimpleMath;

	//速度を計算
	m_velocity = m_addforce * deltatime;

	//オブジェクト移動
	GetObject()->GetTransform()->Translate(m_velocity);

	//速度減少
	m_addforce *= m_reduction;
}

/// <summary>
/// ポジション取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Rigidbody::GetPosition()
{
	return GetObject()->GetTransform()->GetRotatePosition();
}


