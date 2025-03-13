// ================================================================ 
// ファイル名 : Collider.cpp
// 作成者 : 景山碧天
// 説明 :  各当たり判定
// ================================================================
#include"pch.h"
#include"Collider.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonManager/CollisonManager.h"
#include"Base/CommonManager/DebugCollider.h"
#include"Base/Object/Object.h"
#include"Base/Component/Transform/Transform.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
/// <param name="tag">コライダー種類</param>
/// <param name="type">コリジョン種類</param>
/// <param name="rigidbody">リジッドボディ</param>
/// <param name="view">表示フラグ</param>
Collider::Collider(Object* object, ColliderTag tag, CollisionType type, Rigidbody* rigidbody,bool view):Component(object)
	,
	m_colliderTag{ tag },
	m_transform{object->GetTransform()},
	m_rigidbody{ rigidbody },
	m_position{DirectX::SimpleMath::Vector3::Zero},
	m_scale{DirectX::SimpleMath::Vector3::One},
	m_matrix{DirectX::SimpleMath::Matrix::Identity},
	m_isNotPas{ false }
{
	UNREFERENCED_PARAMETER(view);

	//コリジョンマネージャーへの登録
	auto collision = GetObject()->GetScene()->GetCollisionManager();
	collision->AddCollider(this, type);

#if defined(_DEBUG)
	//デバッグ表示の登録
	if (view)
	{
		auto debug = GetObject()->GetScene()->GetDebugCollider();
		debug->AddCollider(this);
	}
#endif
	//matrix初期化
	m_matrix = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

/// <summary>
/// デストラクタ
/// </summary>
Collider::~Collider()
{
	//デバッグ表示から削除
#if defined(_DEBUG)
	auto debug = GetObject()->GetScene()->GetDebugCollider();
	debug->RemoveCollider(this);
#endif
	//コリジョンマネージャーから削除
	auto collision = GetObject()->GetScene()->GetCollisionManager();
	collision->ReMoveCollider(this);
}

/// <summary>
/// ポジションセット
/// </summary>
/// <param name="position">変更ポジション</param>
void Collider::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
	m_matrix = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

/// <summary>
/// スケールセット
/// </summary>
/// <param name="scale">変更スケール</param>
void Collider::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
	m_matrix = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_matrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

/// <summary>
/// ワールドポジション取得
/// </summary>
/// <returns>ワールドポジション</returns>
DirectX::SimpleMath::Vector3 Collider::GetWorldPosition()
{
	return GetTransform().GetRotatePosition() + m_position;
}

/// <summary>
/// ワールドスケール取得
/// </summary>
/// <returns>ワールドスケール</returns>
DirectX::SimpleMath::Vector3 Collider::GetWorldScale()
{
	return GetTransform().GetWorldScale() * m_scale * DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f);
}

/// <summary>
/// matrix取得
/// </summary>
/// <returns>ワールド行列</returns>
DirectX::SimpleMath::Matrix Collider::GetWorldMatrix()
{
	return m_matrix * GetTransform().GetWorldMatrix();
}

/// <summary>
/// バウンディングスフィア用半径取得
/// </summary>
/// <returns>自身の半径</returns>
float Collider::GetRadius()
{
	return 1.0f;
}


//////////////////////////////////////////////////////////////
////////                                           ///////////
////////          AABB                             ///////////
////////                                           ///////////
//////////////////////////////////////////////////////////////


/// <summary>
/// AABB コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
/// <param name="type">コリジョン種類</param>
/// <param name="rigidbody">リジッドボディ</param>
/// <param name="view">表示フラグ</param>
AABB::AABB(Object* object, CollisionType type, Rigidbody* rigidbody, bool view):Collider(object,ColliderTag::AABB,type,rigidbody,view)
{
}

/// <summary>
/// matrix取得(回転を初期化させる)
/// </summary>
/// <returns>位置と大きさのみを対応させた行列</returns>
DirectX::SimpleMath::Matrix AABB::GetWorldMatrix()
{
	Transform trans = GetTransform();
	trans.SetRotate(DirectX::SimpleMath::Quaternion::Identity);
	return trans.GetWorldMatrix();
}

/// <summary>
/// 各軸の大きさ取得
/// </summary>
/// <returns>大きさ</returns>
DirectX::SimpleMath::Vector3 AABB::GetExtents()
{
	return GetObject()->GetTransform()->GetWorldScale() * DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f) * GetScale();
}

/// <summary>
/// 半径取得
/// </summary>
/// <returns>自身の半径</returns>
float AABB::GetRadius()
{
	DirectX::SimpleMath::Vector3 extents = GetExtents();
	return std::sqrtf(extents.x * extents.x + extents.y * extents.y + extents.z * extents.z);
}

//////////////////////////////////////////////////////////////
////////                                           ///////////
////////          OBB                              ///////////
////////                                           ///////////
//////////////////////////////////////////////////////////////

/// <summary>
/// OBB コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
/// <param name="type">コリジョン種類</param>
/// <param name="rigidbody">リジッドボディ</param>
/// <param name="view">表示フラグ</param>
OBB::OBB(Object* object, CollisionType type, Rigidbody* rigidbody, bool view) :Collider(object, ColliderTag::OBB, type, rigidbody, view)
{
}


/// <summary>
///  各軸の大きさ取得
/// </summary>
/// <returns>大きさ</returns>
DirectX::SimpleMath::Vector3 OBB::GetExtents()
{
	return GetObject()->GetTransform()->GetWorldScale() * DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f) * GetScale();
}

/// <summary>
/// 半径取得	
/// </summary>
/// <returns>自身の半径</returns>
float OBB::GetRadius()
{
	DirectX::SimpleMath::Vector3 extents = GetExtents();
	return std::sqrtf(extents.x * extents.x + extents.y * extents.y + extents.z * extents.z);
}

//////////////////////////////////////////////////////////////
////////                                           ///////////
////////          Sphere                           ///////////
////////                                           ///////////
//////////////////////////////////////////////////////////////

/// <summary>
/// 球 コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
/// <param name="type">コリジョン種類</param>
/// <param name="rigidbody">リジッドボディ</param>
/// <param name="view">表示フラグ</param>
/// <param name="radius">半径</param>
Sphere::Sphere(Object* object, CollisionType type, Rigidbody* rigidbody, bool view, float radius) :Collider(object, ColliderTag::SPHERE, type, rigidbody, view)
	,
	m_radius{radius}
{

}

/// <summary>
/// 半径設定
/// </summary>
/// <param name="radius">変更半径</param>
void Sphere::SetRadius(float radius)
{
	m_radius = radius;
}

/// <summary>
/// 半径取得	
/// </summary>
/// <returns>自身の半径</returns>
float Sphere::GetRadius()
{
	DirectX::SimpleMath::Vector3 scale = GetTransform().GetWorldScale();

	return m_radius * std::max(scale.x, std::max(scale.y, scale.z));
}



//////////////////////////////////////////////////////////////
////////                                           ///////////
////////          Segment                          ///////////
////////                                           ///////////
//////////////////////////////////////////////////////////////

/// <summary>
/// 線分 コンストラクタ
/// </summary>
/// <param name="object">所属オブジェクト</param>
/// <param name="type">コリジョン種類</param>
/// <param name="rigidbody">リジッドボディ</param>
/// <param name="view">表示フラグ</param>
/// <param name="start">始点</param>
/// <param name="end">終点</param>
Segment::Segment(Object* object, CollisionType type, Rigidbody* rigidbody, bool view, DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end)
	:Collider(object, ColliderTag::SEGMENT, type, rigidbody, view)
	,
	m_strPos{start},
	m_endPos{end}
{
}

/// <summary>
/// ローカル始点取得
/// </summary>
/// <returns>オブジェクトの座標を考慮しない始点</returns>
DirectX::SimpleMath::Vector3 Segment::GetLocalStartPos()
{
	Transform* trans = GetObject()->GetTransform();
	DirectX::SimpleMath::Vector3 strpos = DirectX::SimpleMath::Vector3::Transform(m_strPos, trans->GetWorldRotate());
	return strpos;
}

/// <summary>
/// ローカル終点取得
/// </summary>
/// <returns>オブジェクトの座標を考慮しない終点</returns>
DirectX::SimpleMath::Vector3 Segment::GetLocalEndPos()
{
	Transform* trans = GetObject()->GetTransform();
	DirectX::SimpleMath::Vector3 endpos = DirectX::SimpleMath::Vector3::Transform(m_endPos, trans->GetWorldRotate());
	return endpos;
}

/// <summary>
/// ワールド始点取得
/// </summary>
/// <returns>オブジェクトの座標を考慮した始点</returns>
DirectX::SimpleMath::Vector3 Segment::GetWorldStartPos()
{
	Transform* trans = GetObject()->GetTransform();
	return trans->GetRotatePosition() + GetLocalStartPos();
}

/// <summary>
///	ワールド終点取得
/// </summary>
/// <returns>オブジェクトの座標を考慮した終点</returns>
DirectX::SimpleMath::Vector3 Segment::GetWorldEndPos()
{
	Transform* trans = GetObject()->GetTransform();
	return trans->GetRotatePosition() + GetLocalEndPos();
}

/// <summary>
/// 始点から終点へのベクトル取得
/// </summary>
/// <returns>始点から終点へのベクトル</returns>
DirectX::SimpleMath::Vector3 Segment::GetVector()
{
	return GetLocalEndPos() - GetLocalStartPos();
}

/// <summary>
/// 始点から終点への向き取得
/// </summary>
/// <returns>始点から終点までの向き</returns>
DirectX::SimpleMath::Vector3 Segment::GetDirection()
{
	DirectX::SimpleMath::Vector3 vec = GetVector();
	vec.Normalize();
	return vec;
}

/// <summary>
/// 長さ取得
/// </summary>
/// <returns>長さ</returns>
float Segment::GetLength()
{
	return GetVector().Length();
}

/// <summary>
/// 半径取得	
/// </summary>
/// <returns>半径</returns>
float Segment::GetRadius()
{
	return GetLength();
}


