// ================================================================ 
// ファイル名 : PlayerWalk.h
// 作成者 : 景山碧天
// 説明 :  プレイヤー歩行状態
// ================================================================

#pragma once
#include"Game/Play/Player/PlayerState/PlayerState.h"
#include"Game/Parameter/PlayerParameter.h"

class CommonResources;
class DirectXInputs;
class Rigidbody;

class PlayerWalk :public PlayerState
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

	bool m_oldIsGraound;

	const PlayerParameter::Parameter* m_parameter;
public:
	//コンストラクタ
	PlayerWalk(PlayerStateMachine* machine, Player* player);
	//デストラクタ
	~PlayerWalk() override = default;
	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
private:
	void Move(float deltatime);
	void Shot();
};