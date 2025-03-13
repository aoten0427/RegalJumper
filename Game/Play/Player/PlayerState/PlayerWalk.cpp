// ================================================================ 
// ファイル名 : PlayerWalk.cpp
// 作成者 : 景山碧天
// 説明 :  プレイヤー歩行状態
// ================================================================
#include"pch.h"
#include"PlayerWalk.h"
#include"Base/Base.h"
#include"Game/Play/Player/Player.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/SpiderAnimation/SpiderAnimatorCenter.h"
#include"MyLib/DebugString.h"

constexpr float MIN_SPEED = 0.1f;//待機状態に戻すスピード値

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">プレイヤーステートマシン</param>
/// <param name="player">プレイヤー</param>
PlayerWalk::PlayerWalk(PlayerStateMachine* machine, Player* player) :PlayerState(machine, player)
	,
	m_player{player},
	m_oldIsGraound{false},
	m_parameter{ PlayerParameter::PARAMETER() }
{
	m_commonResources = player->GetCommonResources();
	m_input = m_commonResources->GetInput();
	m_playerRigidbody = player->GetComponent<Rigidbody>();
}

/// <summary>
/// 事前更新
/// </summary>
void PlayerWalk::PreUpdate()
{
	//アニメーター変更
	SpiderAnimatorCenter* anime = m_player->GetModel()->GetAnimator();
	if (m_player->GetIsGround())
	{
		anime->SetActiveAnimator("PlayerWalk",true);
	}
	else
	{
		anime->SetActiveAnimator("PlayerAir",true);
	}
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
void PlayerWalk::Update(float deltaTime)
{
	

	//重力加算
	float gravity = m_player->GetIsGround() ? m_parameter->GRAVITY_GROUND : m_parameter->GRAVITY_AIR;
	m_playerRigidbody->AddForce(DirectX::SimpleMath::Vector3(0, gravity * deltaTime, 0));
	//移動
	Move(deltaTime);
	//抵抗を計算
	float frection = m_player->GetIsGround() ? m_parameter->FRECTION_GROUND : m_parameter->FRECTION_AIR;
	m_playerRigidbody->AddForce(m_playerRigidbody->GetAddforce() * frection);
	//糸発射
	Shot();

	//アニメーター制御
	if (m_player->GetIsGround() != m_oldIsGraound)
	{
		//アニメーター変更
		SpiderAnimatorCenter* anime = m_player->GetModel()->GetAnimator();
		if (m_player->GetIsGround())
		{
			anime->SetActiveAnimator("PlayerWalk", true);
		}
		else
		{
			anime->SetActiveAnimator("PlayerAir", true);
		}
	}
	

	m_oldIsGraound = m_player->GetIsGround();
}

/// <summary>
/// 事後更新
/// </summary>
void PlayerWalk::PostUpdate()
{
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void PlayerWalk::Move(float deltatime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	if (m_input->IsKeyPress(Keyboard::None))return;
	//加算スピード
	float speed = m_player->GetIsGround() ? m_parameter->SPEED_GROUND : m_parameter->SPEED_AIR;
	bool action = false;

	Transform* transform = m_player->GetTransform();
	//前後左右移動
	if (m_input->IsKeyDown(Keyboard::W))
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(0, 0, 1)) * -speed * deltatime);
		action = true;
	}
	if (m_input->IsKeyDown(Keyboard::S))
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(0, 0, 1)) * speed * deltatime);
		action = true;
	}
	if (m_input->IsKeyDown(Keyboard::A))
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(1, 0, 0)) * -speed * deltatime);
		action = true;
	}
	if (m_input->IsKeyDown(Keyboard::D))
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(1, 0, 0)) * speed * deltatime);
		action = true;
	}
	//ジャンプ
	if (m_input->IsKeyPress(Keyboard::Space)&& m_player->GetIsGround())
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(0, 1, 0)) * m_parameter->JUMP_POWER);
		action = true;
	}


	if (action)return;
	if (!m_player->GetIsGround())return;

	//スピード度が一定以下で待機状態に戻す
	if (abs(m_playerRigidbody->GetVelocity().x) < MIN_SPEED && abs(m_playerRigidbody->GetVelocity().z) < MIN_SPEED)ChangeState(State::IDLE);
}

/// <summary>
/// 発射処理
/// </summary>
void PlayerWalk::Shot()
{
	if (m_input->GetMouseTracker()->leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		ChangeState(State::SHOT);
	}
}
