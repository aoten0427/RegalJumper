#pragma once
#include"Game/Play/Player/PlayerState/PlayerState.h"

class CommonResources;

class PlayerDamage :public PlayerState
{
private:
	CommonResources* m_commonResources;
public:
	PlayerDamage(PlayerStateMachine* machine, Player* player);
	~PlayerDamage() override = default;

	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
};