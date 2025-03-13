// ================================================================ 
// ファイル名 : PlayerIdle.cpp
// 作成者 : 景山碧天
// 説明 :  プレイヤー待機状態
// ================================================================
#include"pch.h"
#include"PlayerIdle.h"
#include"Base/Base.h"
#include"Game/Play/Player/Player.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/SpiderAnimation/SpiderAnimatorCenter.h"
#include"MyLib/DebugString.h"
#include"Game/Parameter/PlayerParameter.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">プレイヤーステートマシン</param>
/// <param name="player">プレイヤー</param>
PlayerIdle::PlayerIdle(PlayerStateMachine* machine, Player* player) :PlayerState(machine, player)
	,
	m_player{player},
	m_parameter{PlayerParameter::PARAMETER()}
{
	m_commonResources = player->GetCommonResources();
	m_input = m_commonResources->GetInput();
	m_playerRigidbody = player->GetComponent<Rigidbody>();
}

/// <summary>
/// 事前更新
/// </summary>
void PlayerIdle::PreUpdate()
{
	//アニメーター変更
	SpiderAnimatorCenter* anime = m_player->GetModel()->GetAnimator();
	anime->SetActiveAnimator("PlayerIdle",true);
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
void PlayerIdle::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	//重力加算
	m_playerRigidbody->AddForce(DirectX::SimpleMath::Vector3(0, m_parameter->GRAVITY_GROUND * deltaTime, 0));
	//抵抗計算
	float fraction = m_player->GetIsGround() ? m_parameter->FRECTION_GROUND : m_parameter->FRECTION_AIR;
	m_playerRigidbody->AddForce(m_playerRigidbody->GetAddforce() * fraction);
	//操作確認
	Operation();
	//糸発射
	Shot();
}

/// <summary>
/// 事後更新
/// </summary>
void PlayerIdle::PostUpdate()
{
}

/// <summary>
/// 移動指示受付
/// </summary>
void PlayerIdle::Operation()
{
	using namespace DirectX;
	if (m_input->IsKeyPress(Keyboard::None))return;
	//移動指示
	if (m_input->IsKeyPress(Keyboard::W) || m_input->IsKeyPress(Keyboard::S) ||
		m_input->IsKeyPress(Keyboard::A) || m_input->IsKeyPress(Keyboard::D))
	{
		ChangeState(State::WALK);
	}
	//ジャンプ
	if (m_input->IsKeyPress(Keyboard::Space) && m_player->GetIsGround())
	{
		m_playerRigidbody->AddForce(m_player->GetTransform()->GetWorldAxisFromLocal(DirectX::SimpleMath::Vector3(0, 1, 0)) * m_parameter->JUMP_POWER);
		ChangeState(State::WALK);
	}
}

/// <summary>
/// 発射
/// </summary>
void PlayerIdle::Shot()
{
	if (m_input->GetMouseTracker()->leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		ChangeState(State::SHOT);
	}
}
