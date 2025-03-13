// ================================================================ 
// ファイル名 : PlayerMoveThread.h
// 作成者 : 景山碧天
// 説明 :  プレイヤー糸での移動状態
// ================================================================

#pragma once
#include"Game/Play/Player/PlayerState/PlayerState.h"
#include"Game/Parameter/PlayerParameter.h"

class CommonResources;
class DirectXInputs;
class Rigidbody;
template<typename...Args>
class Subject;

class PlayerMoveThread :public PlayerState
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
	//発射時サブジェクト
	Subject<>* m_conectSubject;
	//パラメータ
	const PlayerParameter::Parameter* m_parameter;
public:
	//コンストラクタ
	PlayerMoveThread(PlayerStateMachine* machine, Player* player);
	//デストラクタ
	~PlayerMoveThread() override = default;
	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
private:
	//移動
	void Move(float deltatime);
};