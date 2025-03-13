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

	// ���O�X�V����
	void PreUpdate()override;
	// �X�V����
	void Update(float deltaTime)override;
	// ����X�V����
	void PostUpdate()override;
};