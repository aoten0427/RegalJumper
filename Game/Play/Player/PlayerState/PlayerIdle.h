// ================================================================ 
// ファイル名 : PlayerIdle
// 作成者 : 景山碧天
// 説明 :  プレイヤー待機状態
// ================================================================

#pragma once
#include"Game/Play/Player/PlayerState/PlayerState.h"
#include"Game/Parameter/PlayerParameter.h"

class CommonResources;
class DirectXInputs;
class Rigidbody;

class PlayerIdle :public PlayerState
{
private:
	//コモンリソース
	CommonResources* m_commonResources;
	//入力機構
	DirectXInputs* m_input;
	//プレイヤー
	Player* m_player;
	//プレイヤーリジッドボディ
	Rigidbody* m_playerRigidbody;
	//パラメータ
	const PlayerParameter::Parameter* m_parameter;
public:
	//コンストラクタ
	PlayerIdle(PlayerStateMachine* machine, Player* player);
	//デストラクタ
	~PlayerIdle() override = default;
	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
private:
	//移動支持
	void Operation();
	//発射
	void Shot();
};