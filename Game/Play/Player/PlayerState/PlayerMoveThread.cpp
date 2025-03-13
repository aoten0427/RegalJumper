// ================================================================ 
// ファイル名 : PlayerMoveThread.cpp
// 作成者 : 景山碧天
// 説明 :  プレイヤー糸での移動状態
// ================================================================
#include"pch.h"
#include"PlayerMoveThread.h"
#include"Base/Base.h"
#include"Base/Event/Subject.h"
#include"Game/Play/Player/Player.h"
#include"Game/Play/Player/SpiderModel/SpiderModels.h"
#include"Game/Play/Player/SpiderAnimation/SpiderAnimatorCenter.h"
#include"MyLib/DebugString.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">プレイヤーステートマシン</param>
/// <param name="player">プレイヤー</param>
PlayerMoveThread::PlayerMoveThread(PlayerStateMachine* machine, Player* player) :PlayerState(machine, player)
	,
	m_player{ player },
	m_conectSubject{nullptr},
	m_parameter{PlayerParameter::PARAMETER()}
{
	m_commonResources = player->GetCommonResources();
	m_input = m_commonResources->GetInput();
	m_playerRigidbody = player->GetComponent<Rigidbody>();
	m_conectSubject = m_player->AddComponent<Subject<>>(m_player, "PlayerThreadConect");
}

/// <summary>
/// 事前更新
/// </summary>
void PlayerMoveThread::PreUpdate()
{
	//アニメーター変更
	SpiderAnimatorCenter* anime = m_player->GetModel()->GetAnimator();
	anime->SetActiveAnimator("PlayerAir",true);
	m_conectSubject->Notify();
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
void PlayerMoveThread::Update(float deltaTime)
{
	using namespace DirectX::SimpleMath;

	//重力
	m_playerRigidbody->AddForce(Vector3(0, m_parameter->GRAVITY_THREAD * deltaTime, 0));
	//抵抗
	m_playerRigidbody->AddForce(m_playerRigidbody->GetAddforce() * m_parameter->FRECTION_THREAD);
	Move(deltaTime);
}

/// <summary>
/// 事後更新
/// </summary>
void PlayerMoveThread::PostUpdate()
{
	if (!m_player->GetIsGround())
	{
		//アニメーター変更
		SpiderAnimatorCenter* anime = m_player->GetModel()->GetAnimator();
		anime->SetActiveAnimator("PlayerAction", true);
	}
}

/// <summary>
/// 移動
/// </summary>
/// <param name="deltatime">フレーム経過時間</param>
void PlayerMoveThread::Move(float deltatime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	if (m_input->IsKeyPress(Keyboard::None))return;
	Transform* transform = m_player->GetTransform();
	//前後移動
	if (m_input->IsKeyDown(Keyboard::W))
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(0, 0, 1)) * -m_parameter->SPEED_THREAD * deltatime);
	}
	if (m_input->IsKeyDown(Keyboard::S))
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(0, 0, 1)) * m_parameter->SPEED_THREAD * deltatime);
	}
	//ジャンプ
	if (m_input->IsKeyPress(Keyboard::Space) && m_player->GetIsGround())
	{
		m_playerRigidbody->AddForce(transform->GetWorldAxisFromLocal(Vector3(0, 1, 0)) * m_parameter->JUMP_POWER);
	}
}
