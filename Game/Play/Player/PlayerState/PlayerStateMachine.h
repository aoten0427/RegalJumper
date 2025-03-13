// ================================================================ 
// �t�@�C���� : PlayerStateMachine.h
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[�̏�Ԃ��Ǘ�
// ================================================================

#pragma once
#include"Base/MyLibraries/StateMachine/StateMachine.h"
#include"Game/Play/Player/PlayerState/PlayerState.h"

class Player;

class PlayerStateMachine :public StateMachine<PlayerState,PlayerState::State>
{
private:
public:
	PlayerStateMachine(Player* player);
};