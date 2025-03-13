#include"pch.h"
#include"PlayerDamage.h"
#include"Base/Base.h"
#include"Game/Play/Player/Player.h"
#include"MyLib/DebugString.h"

PlayerDamage::PlayerDamage(PlayerStateMachine* machine, Player* player):PlayerState(machine,player)
{
	m_commonResources = player->GetCommonResources();
}

void PlayerDamage::PreUpdate()
{
}

void PlayerDamage::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void PlayerDamage::PostUpdate()
{
}
