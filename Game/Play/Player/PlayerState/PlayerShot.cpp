// ================================================================ 
// ファイル名 : PlayerShot.cpp
// 作成者 : 景山碧天
// 説明 :  プレイヤーショット状態
// ================================================================
#include"pch.h"
#include"PlayerShot.h"
#include"Base/Base.h"
#include"Base/Sound/Sound.h"
#include"Game/Play/Player/PlayerCenter.h"
#include"Game/Play/Player/Player.h"
#include"MyLib/DebugString.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="machine">プレイヤーステートマシン</param>
/// <param name="player">プレイヤー</param>
PlayerShot::PlayerShot(PlayerStateMachine* machine, Player* player) :PlayerState(machine, player)
	,
	m_player{player}
{
	m_commonResources = player->GetCommonResources();
	m_shotSound = m_player->AddComponent<Sound>(m_player, Sound::SoundType::SE, "Shot", false);
}

/// <summary>
/// 事前更新
/// </summary>
void PlayerShot::PreUpdate()
{
	//視線方向
	DirectX::SimpleMath::Vector3 direction = m_player->GetScene()->GetCamera()->GetRayDirection();
	//発射処理
	m_player->GetPlayerCenter()->ThreadShot(direction);
	//音声を鳴らす
	m_shotSound->Play();
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
void PlayerShot::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	ChangeState(State::WALK);
}

/// <summary>
/// 事後更新
/// </summary>
void PlayerShot::PostUpdate()
{
}
