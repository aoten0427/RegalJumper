// ================================================================ 
// ファイル名 :Player.cpp
// 作成者 : 景山碧天
// 説明 :  プレイヤー
// ================================================================
#include"pch.h"
#include"Player.h"
#include"Base/Base.h"
#include"Base/Event/Observer.h"
#include"Base/Event/Subject.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/PlayerState/PlayerStateMachine.h"
#include"Game/Play/Camera/PlayCamera.h"
#include"Game/Play/Thread/ThreadHolder.h"
#include"Game/Parameter/PlayerParameter.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">所属シーン</param>
/// <param name="center">プレイヤーセンター</param>
Player::Player(Scene* scene,PlayerCenter* center):Object(scene)
	,
	m_playerCenter{center},
	m_collider{nullptr},
	m_rigidbody{nullptr},
	m_model{nullptr},
	m_stateMachine{nullptr},
	m_isGround{false}
{
	using namespace DirectX::SimpleMath;

	//リジッドボディ作成
	m_rigidbody = AddComponent<Rigidbody>(this);
	m_rigidbody->SetMass(PlayerParameter::PARAMETER()->MASS);
	//判定作成
	m_collider = AddComponent<OBB>(this, CollisionType::COLLISION, m_rigidbody, false);
	m_collider->SetScale(PlayerParameter::PARAMETER()->COLLIDER_SIZE);
	//モデル作成
	m_model = scene->AddObject<SpiderModels>(scene, this);
	m_model->ChangeState(SpiderModelState::RenderType::NONE);
	//ステートマシン作成
	m_stateMachine = std::make_unique<PlayerStateMachine>(this);
	//カメラ取得
	m_camera = static_cast<PlayCamera*>(GetScene()->GetCamera());
	m_camera->SetPlayer(this);
	//糸保有者機能作成
	ThreadHolder* threadholder = AddComponent<ThreadHolder>(this);
	threadholder->SetConect([&]() {m_stateMachine->ChangeState(PlayerState::State::MOVETHREAD); });
	threadholder->SetCut([&]() {m_stateMachine->ChangeState(PlayerState::State::WALK); });
	//死亡時サブジェクト作成
	m_deathSubject = AddComponent<Subject<>>(this, "PlayerDeath");
	//データリセットオブザーバー作成
	m_resetObserver = AddComponent<Observer<>>(this);
	m_resetObserver->RegistrationSubject("PlayReset");
	m_resetObserver->SetFunction([&]() {Reset(); });
	//初期位置設定
	GetTransform()->SetPosition(PlayerParameter::PARAMETER()->INITIAL_POSITION);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void Player::ObjectUpdate(float deltatime)
{
	using namespace DirectX::SimpleMath;
	//プレイ状態以外は動かさない
	if (GetScene()->GetState() != Scene::State::PLAY)return;

	//回転をカメラから取得
	float rotatin = m_camera->GetRotationY();
	//回転
	GetTransform()->SetRotate(Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(rotatin)));
	//ステートマシンアップデート
	m_stateMachine->Update(deltatime);

	//地上判定のリセット
	m_isGround = false;

	IsDeath();
}

/// <summary>
/// 出現処理
/// </summary>
void Player::Entery()
{
	m_model->ChangeState(SpiderModelState::RenderType::ENTRY);
}

/// <summary>
/// Trigger実行有無 　ゴールとヘルプのみ判定
/// </summary>
/// <param name="collider"></param>
/// <returns></returns>
bool Player::IsTriggerAct(Collider* collider)
{
	if (collider->GetObject()->GetTag() == ObjectTag::Goal)return true;
	if (collider->GetObject()->GetTag() == ObjectTag::Help)return true;
	return false;
}

/// <summary>
/// Collision実行有無　ターゲットボックスは判定しない
/// </summary>
/// <param name="collider"></param>
/// <returns></returns>
bool Player::IsCollisionAct(Collider* collider)
{
	if (collider->GetObject()->GetTag() == ObjectTag::TargetBox)return false;
	return true;
}

/// <summary>
/// 押し出し処理　地上判定を判定
/// </summary>
/// <param name="pushback">押し出し量</param>
void Player::PushBack(DirectX::SimpleMath::Vector3 pushback)
{
	GetTransform()->Translate(pushback);
	//上えの押し出しの場合地面接触フラグをオンにする
	if (pushback.y > 0)m_isGround = true;
}

/// <summary>
/// Trigger処理 ゴール処理
/// </summary>
/// <param name="collider"></param>
void Player::OnTrigger(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
	//ゴール接触処理
	if (collider->GetObject()->GetTag() == ObjectTag::Goal)
	{
		IsGoal();
	}
}

/// <summary>
/// Collision処理
/// </summary>
/// <param name="collider">判定</param>
void Player::OnCollision(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
}

bool Player::IsDetectionAct(Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
	return false;
}

/// <summary>
/// データリセット
/// </summary>
void Player::Reset()
{
	GetTransform()->SetPosition(PlayerParameter::PARAMETER()->INITIAL_POSITION);
	GetTransform()->SetRotate(DirectX::SimpleMath::Quaternion::Identity);
	GetTransform()->TransRotate(DirectX::SimpleMath::Vector3::UnitY, 180.0f);
}

/// <summary>
/// ゴール判定
/// </summary>
void Player::IsGoal()
{
	m_stateMachine->ChangeState(PlayerState::State::IDLE);
	m_stateMachine->ChangeState();

	GetScene()->ChangeState(Scene::State::END);
	m_model->ChangeState(SpiderModelState::RenderType::EXIT);
}

/// <summary>
/// 死亡判定
/// </summary>
void Player::IsDeath()
{
	if (GetTransform()->GetPosition().y < PlayerParameter::PARAMETER()->RESET_HEIGHT)
	{
		m_deathSubject->Notify();
	}
}
