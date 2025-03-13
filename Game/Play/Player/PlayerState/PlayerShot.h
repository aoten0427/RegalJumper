// ================================================================ 
// ファイル名 : PlayerShot
// 作成者 : 景山碧天
// 説明 :  プレイヤーショット状態
// ================================================================

#pragma once
#include"Game/Play/Player/PlayerState/PlayerState.h"

class CommonResources;
class Sound;

class PlayerShot :public PlayerState
{
private:
	//コモンリソース
	CommonResources* m_commonResources;
	//プレイヤー
	Player* m_player;
	//ショットサウンド
	Sound* m_shotSound;
public:
	//コンストラクタ
	PlayerShot(PlayerStateMachine* machine, Player* player);
	//デストラクタ
	~PlayerShot() override = default;
	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
};